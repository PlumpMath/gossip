/* Rectangle and ellipse item types for GossipCanvas widget
 *
 * GossipCanvas is basically a port of the Tk toolkit's most excellent canvas widget.  Tk is
 * copyrighted by the Regents of the University of California, Sun Microsystems, and other parties.
 *
 * Copyright (C) 1998 The Free Software Foundation
 *
 * Author: Federico Mena <federico@nuclecu.unam.mx>
 */

#include <math.h>
#include "gossip-canvas-rect-ellipse.h"
#include "gossip-canvas-util.h"
#include "gossip-art.h"

/* Base class for rectangle and ellipse item types */

#define noVERBOSE

enum {
	ARG_0,
#if 0
	ARG_X1,
	ARG_Y1,
	ARG_X2,
	ARG_Y2,
#endif
	ARG_FILL_COLOR,
	ARG_FILL_COLOR_GDK,
	ARG_FILL_COLOR_RGBA,
	ARG_OUTLINE_COLOR,
	ARG_OUTLINE_COLOR_GDK,
	ARG_OUTLINE_COLOR_RGBA,
	ARG_FILL_STIPPLE,
	ARG_OUTLINE_STIPPLE,
	ARG_WIDTH_PIXELS,
	ARG_WIDTH_UNITS
};


static void gossip_canvas_re_class_init (GossipCanvasREClass *class);
static void gossip_canvas_re_init       (GossipCanvasRE      *re);
static void gossip_canvas_re_destroy    (GtkObject          *object);
static void gossip_canvas_re_set_arg    (GtkObject          *object,
					GtkArg             *arg,
					guint               arg_id);
static void gossip_canvas_re_get_arg    (GtkObject          *object,
					GtkArg             *arg,
					guint               arg_id);

static void gossip_canvas_re_set_coords (GossipCanvasItem *item, int n_coords, double *coords);
static void gossip_canvas_re_update_shared      (GossipCanvasItem *item, double *affine, int flags);
static void gossip_canvas_re_realize     (GossipCanvasItem *item);
static void gossip_canvas_re_unrealize   (GossipCanvasItem *item);
static void gossip_canvas_re_translate   (GossipCanvasItem *item, double dx, double dy);
static void gossip_canvas_re_bounds      (GossipCanvasItem *item, double *x1, double *y1, double *x2, double *y2);

#if 0
static void gossip_canvas_re_render      (GossipCanvasItem *item, GossipCanvasBuf *buf);
#endif

static void gossip_canvas_rect_update      (GossipCanvasItem *item, double *affine, int flags);
static void gossip_canvas_ellipse_update      (GossipCanvasItem *item, double *affine, int flags);

static GossipCanvasItemClass *re_parent_class;


GtkType
gossip_canvas_re_get_type (void)
{
	static GtkType re_type = 0;

	if (!re_type) {
		GtkTypeInfo re_info = {
			"GossipCanvasRE",
			sizeof (GossipCanvasRE),
			sizeof (GossipCanvasREClass),
			(GtkClassInitFunc) gossip_canvas_re_class_init,
			(GtkObjectInitFunc) gossip_canvas_re_init,
			NULL, /* reserved_1 */
			NULL, /* reserved_2 */
			(GtkClassInitFunc) NULL
		};

		re_type = gtk_type_unique (gossip_canvas_item_get_type (), &re_info);
	}

	return re_type;
}

static void
gossip_canvas_re_class_init (GossipCanvasREClass *class)
{
	GtkObjectClass *object_class;
	GossipCanvasItemClass *item_class;

	object_class = (GtkObjectClass *) class;
	item_class = (GossipCanvasItemClass *) class;

	re_parent_class = gtk_type_class (gossip_canvas_item_get_type ());

#if 0
	gtk_object_add_arg_type ("GossipCanvasRE::x1", GTK_TYPE_DOUBLE, GTK_ARG_READWRITE, ARG_X1);
	gtk_object_add_arg_type ("GossipCanvasRE::y1", GTK_TYPE_DOUBLE, GTK_ARG_READWRITE, ARG_Y1);
	gtk_object_add_arg_type ("GossipCanvasRE::x2", GTK_TYPE_DOUBLE, GTK_ARG_READWRITE, ARG_X2);
	gtk_object_add_arg_type ("GossipCanvasRE::y2", GTK_TYPE_DOUBLE, GTK_ARG_READWRITE, ARG_Y2);
#endif
	gtk_object_add_arg_type ("GossipCanvasRE::fill_color", GTK_TYPE_STRING, GTK_ARG_WRITABLE, ARG_FILL_COLOR);
	gtk_object_add_arg_type ("GossipCanvasRE::fill_color_gdk", GTK_TYPE_GDK_COLOR, GTK_ARG_READWRITE, ARG_FILL_COLOR_GDK);
	gtk_object_add_arg_type ("GossipCanvasRE::fill_color_rgba", GTK_TYPE_UINT, GTK_ARG_READWRITE, ARG_FILL_COLOR_RGBA);
	gtk_object_add_arg_type ("GossipCanvasRE::outline_color", GTK_TYPE_STRING, GTK_ARG_WRITABLE, ARG_OUTLINE_COLOR);
	gtk_object_add_arg_type ("GossipCanvasRE::outline_color_gdk", GTK_TYPE_GDK_COLOR, GTK_ARG_READWRITE, ARG_OUTLINE_COLOR_GDK);
	gtk_object_add_arg_type ("GossipCanvasRE::outline_color_rgba", GTK_TYPE_UINT, GTK_ARG_READWRITE, ARG_OUTLINE_COLOR_RGBA);
	gtk_object_add_arg_type ("GossipCanvasRE::fill_stipple", GTK_TYPE_GDK_WINDOW, GTK_ARG_READWRITE, ARG_FILL_STIPPLE);
	gtk_object_add_arg_type ("GossipCanvasRE::outline_stipple", GTK_TYPE_GDK_WINDOW, GTK_ARG_READWRITE, ARG_OUTLINE_STIPPLE);
	gtk_object_add_arg_type ("GossipCanvasRE::width_pixels", GTK_TYPE_UINT, GTK_ARG_WRITABLE, ARG_WIDTH_PIXELS);
	gtk_object_add_arg_type ("GossipCanvasRE::width_units", GTK_TYPE_DOUBLE, GTK_ARG_WRITABLE, ARG_WIDTH_UNITS);

	object_class->destroy = gossip_canvas_re_destroy;
	object_class->set_arg = gossip_canvas_re_set_arg;
	object_class->get_arg = gossip_canvas_re_get_arg;

	item_class->set_coords = gossip_canvas_re_set_coords;
	item_class->realize = gossip_canvas_re_realize;
	item_class->unrealize = gossip_canvas_re_unrealize;
	item_class->translate = gossip_canvas_re_translate;
	item_class->bounds = gossip_canvas_re_bounds;

#if 0
	item_class->render = gossip_canvas_re_render;
#endif
}

static void
gossip_canvas_re_init (GossipCanvasRE *re)
{
	re->x1 = 0.0;
	re->y1 = 0.0;
	re->x2 = 0.0;
	re->y2 = 0.0;
	re->width = 0.0;
#if 0
	re->fill_svp = NULL;
	re->outline_svp = NULL;
#endif
}

static void
gossip_canvas_re_destroy (GtkObject *object)
{
	GossipCanvasRE *re;

	g_return_if_fail (object != NULL);
	g_return_if_fail (GOSSIP_IS_CANVAS_RE (object));

	re = GOSSIP_CANVAS_RE (object);

	if (re->fill_stipple)
		gdk_bitmap_unref (re->fill_stipple);

	if (re->outline_stipple)
		gdk_bitmap_unref (re->outline_stipple);

#if 0
	if (re->fill_svp)
		art_svp_free (re->fill_svp);

	if (re->outline_svp)
		art_svp_free (re->outline_svp);
#endif

	if (GTK_OBJECT_CLASS (re_parent_class)->destroy)
		(* GTK_OBJECT_CLASS (re_parent_class)->destroy) (object);
}

static void get_bounds (GossipCanvasRE *re, double *px1, double *py1, double *px2, double *py2)
{
	GossipCanvasItem *item;
	double x1, y1, x2, y2;
	int cx1, cy1, cx2, cy2;
	double hwidth;

#ifdef VERBOSE
	g_print ("re get_bounds\n");
#endif
	item = GOSSIP_CANVAS_ITEM (re);

	if (re->width_pixels)
		hwidth = (re->width / item->canvas->pixels_per_unit) / 2.0;
	else
		hwidth = re->width / 2.0;

	x1 = re->x1;
	y1 = re->y1;
	x2 = re->x2;
	y2 = re->y2;

	gossip_canvas_item_i2w (item, &x1, &y1);
	gossip_canvas_item_i2w (item, &x2, &y2);
	gossip_canvas_w2c (item->canvas, x1 - hwidth, y1 - hwidth, &cx1, &cy1);
	gossip_canvas_w2c (item->canvas, x2 + hwidth, y2 + hwidth, &cx2, &cy2);
	*px1 = cx1;
	*py1 = cy1;
	*px2 = cx2;
	*py2 = cy2;

	/* Some safety fudging */

	*px1 -= 2;
	*py1 -= 2;
	*px2 += 2;
	*py2 += 2;
}

/* deprecated */
static void
recalc_bounds (GossipCanvasRE *re)
{
	GossipCanvasItem *item;
	double x1, y1, x2, y2;
	int cx1, cy1, cx2, cy2;
	double hwidth;

#ifdef VERBOSE
	g_print ("re recalc_bounds\n");
#endif
	item = GOSSIP_CANVAS_ITEM (re);

	get_bounds (re, &item->x1, &item->y1, &item->x2, &item->y2);

	gossip_canvas_group_child_bounds (GOSSIP_CANVAS_GROUP (item->parent), item);
}

/* Convenience function to set a GC's foreground color to the specified pixel value */
static void
set_gc_foreground (GdkGC *gc, gulong pixel)
{
	GdkColor c;

	if (!gc)
		return;

	c.pixel = pixel;
	gdk_gc_set_foreground (gc, &c);
}

/* Sets the stipple pattern for the specified gc */
static void
set_stipple (GdkGC *gc, GdkBitmap **internal_stipple, GdkBitmap *stipple, int reconfigure)
{
	if (*internal_stipple && !reconfigure)
		gdk_bitmap_unref (*internal_stipple);

	*internal_stipple = stipple;
	if (stipple && !reconfigure)
		gdk_bitmap_ref (stipple);

	if (gc) {
		if (stipple) {
			gdk_gc_set_stipple (gc, stipple);
			gdk_gc_set_fill (gc, GDK_STIPPLED);
		} else
			gdk_gc_set_fill (gc, GDK_SOLID);
	}
}

/* Recalculate the outline width of the rectangle/ellipse and set it in its GC */
static void
set_outline_gc_width (GossipCanvasRE *re)
{
	int width;

	if (!re->outline_gc)
		return;

	if (re->width_pixels)
		width = (int) re->width;
	else
		width = (int) (re->width * re->item.canvas->pixels_per_unit + 0.5);

	gdk_gc_set_line_attributes (re->outline_gc, width,
				    GDK_LINE_SOLID, GDK_CAP_PROJECTING, GDK_JOIN_MITER);
}


static void
gossip_canvas_re_set_fill (GossipCanvasRE *re, gboolean fill_set)
{
	if (re->fill_set != fill_set) {
		re->fill_set = fill_set;
		gossip_canvas_item_request_update (GOSSIP_CANVAS_ITEM (re));
	}
}

static void
gossip_canvas_re_set_outline (GossipCanvasRE *re, gboolean outline_set)
{
	if (re->outline_set != outline_set) {
		re->outline_set = outline_set;
		gossip_canvas_item_request_update (GOSSIP_CANVAS_ITEM (re));
	}
}

static void
gossip_canvas_re_set_coords (GossipCanvasItem *item, int n_coords, double *coords)
{
  if (n_coords >= 4)
    {
      GossipCanvasRE *re = GOSSIP_CANVAS_RE(item);
      re->x1 = coords[0];
      re->y1 = coords[1];
      re->x2 = coords[2];
      re->y2 = coords[3];
      gossip_canvas_item_request_update (item);
    }
}

static void
gossip_canvas_re_set_arg (GtkObject *object, GtkArg *arg, guint arg_id)
{
	GossipCanvasItem *item;
	GossipCanvasRE *re;
	GdkColor color;
	GdkColor *colorp;

	item = GOSSIP_CANVAS_ITEM (object);
	re = GOSSIP_CANVAS_RE (object);

	switch (arg_id) {
#if 0
	case ARG_X1:
		re->x1 = GTK_VALUE_DOUBLE (*arg);

		gossip_canvas_item_request_update (item);
		break;

	case ARG_Y1:
		re->y1 = GTK_VALUE_DOUBLE (*arg);

		gossip_canvas_item_request_update (item);
		break;

	case ARG_X2:
		re->x2 = GTK_VALUE_DOUBLE (*arg);

		gossip_canvas_item_request_update (item);
		break;

	case ARG_Y2:
		re->y2 = GTK_VALUE_DOUBLE (*arg);

		gossip_canvas_item_request_update (item);
		break;
#endif

	case ARG_FILL_COLOR:
		if (gossip_canvas_get_color (item->canvas, GTK_VALUE_STRING (*arg), &color)) {
			gossip_canvas_re_set_fill (re, TRUE);
			re->fill_pixel = color.pixel;
#if 0
			if (item->canvas->aa) {
				re->fill_color =
					((color.red & 0xff00) << 16) |
					((color.green & 0xff00) << 8) |
					(color.blue & 0xff00) |
					0xff;
#ifdef VERBOSE			       
				g_print ("re fill color = %08x\n", re->fill_color);
#endif
			}
			else
#endif
				set_gc_foreground (re->fill_gc, re->fill_pixel);
		} else {
			gossip_canvas_re_set_fill (re, FALSE);
			re->fill_color = 0;
		}

		gossip_canvas_item_request_update (item);
		break;

	case ARG_FILL_COLOR_GDK:
		gossip_canvas_re_set_fill (re, TRUE);
		colorp = (GdkColor *) GTK_VALUE_BOXED (*arg);
		re->fill_pixel = colorp->pixel;

#if 0
		if (item->canvas->aa)
			re->fill_color = (((colorp->red & 0xff00) << 16) |
					  ((colorp->green & 0xff00) << 8) |
					  (colorp->blue & 0xff00) |
					  0xff);
		else
#endif
			set_gc_foreground (re->fill_gc, re->fill_pixel);

		gossip_canvas_item_request_update (item);
		break;

	case ARG_FILL_COLOR_RGBA:
		gossip_canvas_re_set_fill (re, TRUE);
		re->fill_set = TRUE;
		re->fill_color = GTK_VALUE_UINT (*arg);

		gossip_canvas_item_request_update (item);
		break;

	case ARG_OUTLINE_COLOR:
		if (gossip_canvas_get_color (item->canvas, GTK_VALUE_STRING (*arg), &color)) {
#ifdef VERBOSE
			g_print ("re outline color %x %x %x\n", color.red, color.green, color.blue);
#endif
			gossip_canvas_re_set_outline (re, TRUE);
			re->outline_pixel = color.pixel;
#if 0
			if (item->canvas->aa)
				re->outline_color =
					((color.red & 0xff00) << 16) |
					((color.green & 0xff00) << 8) |
					(color.blue & 0xff00) |
					0xff;
			else
#endif
				set_gc_foreground (re->outline_gc, re->outline_pixel);
		} else {
			gossip_canvas_re_set_outline (re, FALSE);
			re->outline_color = 0;
		}

		gossip_canvas_item_request_update (item);
		break;

	case ARG_OUTLINE_COLOR_GDK:
		gossip_canvas_re_set_outline (re, TRUE);
		colorp = (GdkColor *) GTK_VALUE_BOXED (*arg);
		re->outline_set = TRUE;
		re->outline_pixel = colorp->pixel;

#if 0
		if (item->canvas->aa)
			re->outline_color = (((colorp->red & 0xff00) << 16) |
					     ((colorp->green & 0xff00) << 8) |
					     (colorp->blue & 0xff00) |
					     0xff);
		else
#endif
			set_gc_foreground (re->outline_gc, re->outline_pixel);

		gossip_canvas_item_request_update (item);
		break;

	case ARG_OUTLINE_COLOR_RGBA:
		gossip_canvas_re_set_outline (re, TRUE);
		re->outline_color = GTK_VALUE_UINT (*arg);

		gossip_canvas_item_request_update (item);

		break;

	case ARG_FILL_STIPPLE:
#if 0
		if (!item->canvas->aa)
#endif
			set_stipple (re->fill_gc, &re->fill_stipple, GTK_VALUE_BOXED (*arg), FALSE);
		break;

	case ARG_OUTLINE_STIPPLE:
#if 0
		if (!item->canvas->aa)
#endif
			set_stipple (re->outline_gc, &re->outline_stipple, GTK_VALUE_BOXED (*arg), FALSE);
		break;
		
	case ARG_WIDTH_PIXELS:
		re->width = GTK_VALUE_UINT (*arg);
		re->width_pixels = TRUE;
#if 0
		if (!item->canvas->aa)
#endif
			set_outline_gc_width (re);

		gossip_canvas_item_request_update (item);
	
		break;

	case ARG_WIDTH_UNITS:
		re->width = fabs (GTK_VALUE_DOUBLE (*arg));
		re->width_pixels = FALSE;
#if 0
		if (!item->canvas->aa)
#endif
			set_outline_gc_width (re);

		gossip_canvas_item_request_update (item);

		break;

	default:
		break;
	}
}

/* Allocates a GdkColor structure filled with the specified pixel, and puts it into the specified
 * arg for returning it in the get_arg method.
 */
static void
get_color_arg (GossipCanvasRE *re, gulong pixel, GtkArg *arg)
{
	GdkColor *color;

	color = g_new (GdkColor, 1);
	color->pixel = pixel;
	gdk_color_context_query_color (GOSSIP_CANVAS_ITEM (re)->canvas->cc, color);
	GTK_VALUE_BOXED (*arg) = color;
}

static void
gossip_canvas_re_get_arg (GtkObject *object, GtkArg *arg, guint arg_id)
{
	GossipCanvasRE *re;

	re = GOSSIP_CANVAS_RE (object);

	switch (arg_id) {
#if 0
	case ARG_X1:
		GTK_VALUE_DOUBLE (*arg) = re->x1;
		break;

	case ARG_Y1:
		GTK_VALUE_DOUBLE (*arg) = re->y1;
		break;

	case ARG_X2:
		GTK_VALUE_DOUBLE (*arg) = re->x2;
		break;

	case ARG_Y2:
		GTK_VALUE_DOUBLE (*arg) = re->y2;
		break;
#endif

	case ARG_FILL_COLOR_GDK:
		get_color_arg (re, re->fill_pixel, arg);
		break;

	case ARG_OUTLINE_COLOR_GDK:
		get_color_arg (re, re->outline_pixel, arg);
		break;

	case ARG_FILL_COLOR_RGBA:
		GTK_VALUE_UINT (*arg) = re->fill_color;
		break;

	case ARG_OUTLINE_COLOR_RGBA:
		GTK_VALUE_UINT (*arg) = re->outline_color;
		break;

	case ARG_FILL_STIPPLE:
		GTK_VALUE_BOXED (*arg) = re->fill_stipple;
		break;

	case ARG_OUTLINE_STIPPLE:
		GTK_VALUE_BOXED (*arg) = re->outline_stipple;
		break;

	default:
		arg->type = GTK_TYPE_INVALID;
		break;
	}
}

static void
gossip_canvas_re_update_shared (GossipCanvasItem *item, double *affine, int flags)
{
	GossipCanvasRE *re;

#ifdef VERBOSE
	g_print ("gossip_canvas_re_update_shared\n");
#endif
	re = GOSSIP_CANVAS_RE (item);

	if (re_parent_class->update)
		(* re_parent_class->update) (item, affine, flags);

#if 0
	if (!item->canvas->aa) 
#endif
	  {
		set_gc_foreground (re->fill_gc, re->fill_pixel);
		set_gc_foreground (re->outline_gc, re->outline_pixel);
		set_stipple (re->fill_gc, &re->fill_stipple, re->fill_stipple, TRUE);
		set_stipple (re->outline_gc, &re->outline_stipple, re->outline_stipple, TRUE);
		set_outline_gc_width (re);
	} 

#ifdef OLD_XFORM
	recalc_bounds (re);
#endif
}

static void
gossip_canvas_re_realize (GossipCanvasItem *item)
{
	GossipCanvasRE *re;

#ifdef VERBOSE
	g_print ("gossip_canvas_re_realize\n");
#endif
	re = GOSSIP_CANVAS_RE (item);

	if (re_parent_class->realize)
		(* re_parent_class->realize) (item);

#if 0
	if (!item->canvas->aa) 
#endif
	  {
		re->fill_gc = gdk_gc_new (item->canvas->layout.bin_window);
		re->outline_gc = gdk_gc_new (item->canvas->layout.bin_window);
	}

#ifdef OLD_XFORM
	(* GOSSIP_CANVAS_ITEM_CLASS (item->object.klass)->update) (item, NULL, NULL, 0);
#endif
}

static void
gossip_canvas_re_unrealize (GossipCanvasItem *item)
{
	GossipCanvasRE *re;

	re = GOSSIP_CANVAS_RE (item);

#if 0
	if (!item->canvas->aa) 
#endif
	  {
		gdk_gc_unref (re->fill_gc);
		gdk_gc_unref (re->outline_gc);
	}

	if (re_parent_class->unrealize)
		(* re_parent_class->unrealize) (item);
}

static void
gossip_canvas_re_translate (GossipCanvasItem *item, double dx, double dy)
{
	GossipCanvasRE *re;

#ifdef VERBOSE
	g_print ("gossip_canvas_re_translate %g %g\n", dx, dy);
#endif
	re = GOSSIP_CANVAS_RE (item);

	re->x1 += dx;
	re->y1 += dy;
	re->x2 += dx;
	re->y2 += dy;

	recalc_bounds (re);

#ifdef VERBOSE
	g_print ("translate\n");
#endif
#if 0
	if (item->canvas->aa) {
		gossip_canvas_item_request_update (item);
	}
#endif
}

static void
gossip_canvas_re_bounds (GossipCanvasItem *item, double *x1, double *y1, double *x2, double *y2)
{
	GossipCanvasRE *re;
	double hwidth;

#ifdef VERBOSE
	g_print ("gossip_canvas_re_bounds\n");
#endif
	re = GOSSIP_CANVAS_RE (item);

	if (re->width_pixels)
		hwidth = (re->width / item->canvas->pixels_per_unit) / 2.0;
	else
		hwidth = re->width / 2.0;

	*x1 = re->x1 - hwidth;
	*y1 = re->y1 - hwidth;
	*x2 = re->x2 + hwidth;
	*y2 = re->y2 + hwidth;
}

#if 0
static void
gossip_canvas_re_render (GossipCanvasItem *item,
			GossipCanvasBuf *buf)
{
	GossipCanvasRE *re;
	guint32 fg_color, bg_color;

	re = GOSSIP_CANVAS_RE (item);

#ifdef VERBOSE
	g_print ("gossip_canvas_re_render (%d, %d) - (%d, %d) fill=%08x outline=%08x\n",
		 buf->rect.x0, buf->rect.y0, buf->rect.x1, buf->rect.y1, re->fill_color, re->outline_color);
#endif

	if (re->fill_svp != NULL) {
		gossip_canvas_render_svp (buf, re->fill_svp, re->fill_color);
	}

	if (re->outline_svp != NULL) {
		gossip_canvas_render_svp (buf, re->outline_svp, re->outline_color);
	}
}
#endif

/* Rectangle item */


static void gossip_canvas_rect_class_init (GossipCanvasRectClass *class);

static void   gossip_canvas_rect_draw   (GossipCanvasItem *item, GdkDrawable *drawable, int x, int y, int width, int height);
static double gossip_canvas_rect_point  (GossipCanvasItem *item, double x, double y, int cx, int cy,
				        GossipCanvasItem **actual_item);


GtkType
gossip_canvas_rect_get_type (void)
{
	static GtkType rect_type = 0;

	if (!rect_type) {
		GtkTypeInfo rect_info = {
			"GossipCanvasRect",
			sizeof (GossipCanvasRect),
			sizeof (GossipCanvasRectClass),
			(GtkClassInitFunc) gossip_canvas_rect_class_init,
			(GtkObjectInitFunc) NULL,
			NULL, /* reserved_1 */
			NULL, /* reserved_2 */
			(GtkClassInitFunc) NULL
		};

		rect_type = gtk_type_unique (gossip_canvas_re_get_type (), &rect_info);
	}

	return rect_type;
}

static void
gossip_canvas_rect_class_init (GossipCanvasRectClass *class)
{
	GossipCanvasItemClass *item_class;

	item_class = (GossipCanvasItemClass *) class;

	item_class->draw = gossip_canvas_rect_draw;
	item_class->point = gossip_canvas_rect_point;
	item_class->update = gossip_canvas_rect_update;
}

static void
gossip_canvas_rect_draw (GossipCanvasItem *item, GdkDrawable *drawable, int x, int y, int width, int height)
{
	GossipCanvasRE *re;
	double i2w[6], w2c[6], i2c[6];
	int x1, y1, x2, y2;
	ArtPoint i1, i2;
	ArtPoint c1, c2;

	re = GOSSIP_CANVAS_RE (item);

	/* Get canvas pixel coordinates */

	gossip_canvas_item_i2w_affine (item, i2w);
	gossip_canvas_w2c_affine (item->canvas, w2c);
	art_affine_multiply (i2c, i2w, w2c);

	i1.x = re->x1;
	i1.y = re->y1;
	i2.x = re->x2;
	i2.y = re->y2;
	art_affine_point (&c1, &i1, i2c);
	art_affine_point (&c2, &i2, i2c);
	x1 = c1.x;
	y1 = c1.y;
	x2 = c2.x;
	y2 = c2.y;
	
	if (re->fill_set) {
		if (re->fill_stipple)
			gossip_canvas_set_stipple_origin (item->canvas, re->fill_gc);

		gdk_draw_rectangle (drawable,
				    re->fill_gc,
				    TRUE,
				    x1 - x,
				    y1 - y,
				    x2 - x1 + 1,
				    y2 - y1 + 1);
	}

	if (re->outline_set) {
		if (re->outline_stipple)
			gossip_canvas_set_stipple_origin (item->canvas, re->outline_gc);

		gdk_draw_rectangle (drawable,
				    re->outline_gc,
				    FALSE,
				    x1 - x,
				    y1 - y,
				    x2 - x1,
				    y2 - y1);
	}
}

static double
gossip_canvas_rect_point (GossipCanvasItem *item, double x, double y, int cx, int cy, GossipCanvasItem **actual_item)
{
	GossipCanvasRE *re;
	double x1, y1, x2, y2;
	double hwidth;
	double dx, dy;
	double tmp;

#ifdef VERBOSE
	g_print ("gossip_canvas_rect_point\n");
#endif
	re = GOSSIP_CANVAS_RE (item);

	*actual_item = item;

	/* Find the bounds for the rectangle plus its outline width */

	x1 = re->x1;
	y1 = re->y1;
	x2 = re->x2;
	y2 = re->y2;

	if (re->outline_set) {
		if (re->width_pixels)
			hwidth = (re->width / item->canvas->pixels_per_unit) / 2.0;
		else
			hwidth = re->width / 2.0;

		x1 -= hwidth;
		y1 -= hwidth;
		x2 += hwidth;
		y2 += hwidth;
	} else
		hwidth = 0.0;

	/* Is point inside rectangle (which can be hollow if it has no fill set)? */

	if ((x >= x1) && (y >= y1) && (x <= x2) && (y <= y2)) {
		if (re->fill_set || !re->outline_set)
		  return 0.0;

		dx = x - x1;
		tmp = x2 - x;
		if (tmp < dx)
			dx = tmp;

		dy = y - y1;
		tmp = y2 - y;
		if (tmp < dy)
			dy = tmp;

		if (dy < dx)
			dx = dy;

		dx -= 2.0 * hwidth;

		if (dx < 0.0)
			return 0.0;
		else
			return dx;
	}

	/* Point is outside rectangle */

	if (x < x1)
		dx = x1 - x;
	else if (x > x2)
		dx = x - x2;
	else
		dx = 0.0;

	if (y < y1)
		dy = y1 - y;
	else if (y > y2)
		dy = y - y2;
	else
		dy = 0.0;

	return sqrt (dx * dx + dy * dy);
}

static void
gossip_canvas_rect_update (GossipCanvasItem *item, double affine[6], gint flags)
{
	GossipCanvasRE *re;
#if 0
	ArtVpath vpath[11];
	ArtVpath *vpath2;
#endif
	double x0, y0, x1, y1;
	double dx, dy;
	double halfwidth;
	int i;

#ifdef VERBOSE
	{
		char str[128];

		art_affine_to_string (str, affine);
		g_print ("gossip_canvas_rect_update item %x %s\n", item, str);

		if (item->xform) {
		  g_print ("xform = %g %g\n", item->xform[0], item->xform[1]);
		}
	}
#endif
	gossip_canvas_re_update_shared (item, affine, flags);

	re = GOSSIP_CANVAS_RE (item);

#if 0
	if (item->canvas->aa) 
	  {
		x0 = re->x1;
		y0 = re->y1;
		x1 = re->x2;
		y1 = re->y2;

		gossip_canvas_item_reset_bounds (item);

		if (re->fill_set) {
			vpath[0].code = ART_MOVETO;
			vpath[0].x = x0;
			vpath[0].y = y0;
			vpath[1].code = ART_LINETO;
			vpath[1].x = x0;
			vpath[1].y = y1;
			vpath[2].code = ART_LINETO;
			vpath[2].x = x1;
			vpath[2].y = y1;
			vpath[3].code = ART_LINETO;
			vpath[3].x = x1;
			vpath[3].y = y0;
			vpath[4].code = ART_LINETO;
			vpath[4].x = x0;
			vpath[4].y = y0;
			vpath[5].code = ART_END;
			vpath[5].x = 0;
			vpath[5].y = 0;

			vpath2 = art_vpath_affine_transform (vpath, affine);

			gossip_canvas_item_update_svp_clip (item, &re->fill_svp, art_svp_from_vpath (vpath2), clip_path);
			art_free (vpath2);
		} else
			gossip_canvas_item_update_svp (item, &re->fill_svp, NULL);

		if (re->outline_set) {
			/* We do the stroking by hand because it's simple enough
			   and could save time. */

			if (re->width_pixels)
				halfwidth = re->width * 0.5;
			else
				halfwidth = re->width * item->canvas->pixels_per_unit * 0.5;

			if (halfwidth < 0.25)
				halfwidth = 0.25;

			i = 0;
			vpath[i].code = ART_MOVETO;
			vpath[i].x = x0 - halfwidth;
			vpath[i].y = y0 - halfwidth;
			i++;
			vpath[i].code = ART_LINETO;
			vpath[i].x = x0 - halfwidth;
			vpath[i].y = y1 + halfwidth;
			i++;
			vpath[i].code = ART_LINETO;
			vpath[i].x = x1 + halfwidth;
			vpath[i].y = y1 + halfwidth;
			i++;
			vpath[i].code = ART_LINETO;
			vpath[i].x = x1 + halfwidth;
			vpath[i].y = y0 - halfwidth;
			i++;
			vpath[i].code = ART_LINETO;
			vpath[i].x = x0 - halfwidth;
			vpath[i].y = y0 - halfwidth;
			i++;

			if (x1 - halfwidth > x0 + halfwidth &&
			    y1 - halfwidth > y0 + halfwidth) {
				vpath[i].code = ART_MOVETO;
				vpath[i].x = x0 + halfwidth;
				vpath[i].y = y0 + halfwidth;
				i++;
				vpath[i].code = ART_LINETO;
				vpath[i].x = x1 - halfwidth;
				vpath[i].y = y0 + halfwidth;
				i++;
				vpath[i].code = ART_LINETO;
				vpath[i].x = x1 - halfwidth;
				vpath[i].y = y1 - halfwidth;
				i++;
				vpath[i].code = ART_LINETO;
				vpath[i].x = x0 + halfwidth;
				vpath[i].y = y1 - halfwidth;
				i++;
				vpath[i].code = ART_LINETO;
				vpath[i].x = x0 + halfwidth;
				vpath[i].y = y0 + halfwidth;
				i++;
			}
			vpath[i].code = ART_END;
			vpath[i].x = 0;
			vpath[i].y = 0;

			vpath2 = art_vpath_affine_transform (vpath, affine);

			gossip_canvas_item_update_svp_clip (item, &re->outline_svp, art_svp_from_vpath (vpath2), clip_path);
			art_free (vpath2);
		} else
			gossip_canvas_item_update_svp (item, &re->outline_svp, NULL);
	} else 
#endif
	  {
		/* xlib rendering - just update the bbox */
		get_bounds (re, &x0, &y0, &x1, &y1);
		gossip_canvas_update_bbox (item, x0, y0, x1, y1);
	}
}

/* Ellipse item */


static void gossip_canvas_ellipse_class_init (GossipCanvasEllipseClass *class);

static void   gossip_canvas_ellipse_draw   (GossipCanvasItem *item, GdkDrawable *drawable, int x, int y,
					   int width, int height);
static double gossip_canvas_ellipse_point  (GossipCanvasItem *item, double x, double y, int cx, int cy,
					   GossipCanvasItem **actual_item);


GtkType
gossip_canvas_ellipse_get_type (void)
{
	static GtkType ellipse_type = 0;

	if (!ellipse_type) {
		GtkTypeInfo ellipse_info = {
			"GossipCanvasEllipse",
			sizeof (GossipCanvasEllipse),
			sizeof (GossipCanvasEllipseClass),
			(GtkClassInitFunc) gossip_canvas_ellipse_class_init,
			(GtkObjectInitFunc) NULL,
			NULL, /* reserved_1 */
			NULL, /* reserved_2 */
			(GtkClassInitFunc) NULL
		};

		ellipse_type = gtk_type_unique (gossip_canvas_re_get_type (), &ellipse_info);
	}

	return ellipse_type;
}

static void
gossip_canvas_ellipse_class_init (GossipCanvasEllipseClass *class)
{
	GossipCanvasItemClass *item_class;

	item_class = (GossipCanvasItemClass *) class;

	item_class->draw = gossip_canvas_ellipse_draw;
	item_class->point = gossip_canvas_ellipse_point;
	item_class->update = gossip_canvas_ellipse_update;
}

static void
gossip_canvas_ellipse_draw (GossipCanvasItem *item, GdkDrawable *drawable, int x, int y, int width, int height)
{
	GossipCanvasRE *re;
	double i2w[6], w2c[6], i2c[6];
	int x1, y1, x2, y2;
	ArtPoint i1, i2;
	ArtPoint c1, c2;

	re = GOSSIP_CANVAS_RE (item);

	/* Get canvas pixel coordinates */

	gossip_canvas_item_i2w_affine (item, i2w);
	gossip_canvas_w2c_affine (item->canvas, w2c);
	art_affine_multiply (i2c, i2w, w2c);

	i1.x = re->x1;
	i1.y = re->y1;
	i2.x = re->x2;
	i2.y = re->y2;
	art_affine_point (&c1, &i1, i2c);
	art_affine_point (&c2, &i2, i2c);
	x1 = c1.x;
	y1 = c1.y;
	x2 = c2.x;
	y2 = c2.y;
	
	if (re->fill_set) {
		if (re->fill_stipple)
			gossip_canvas_set_stipple_origin (item->canvas, re->fill_gc);
		
		gdk_draw_arc (drawable,
			      re->fill_gc,
			      TRUE,
			      x1 - x,
			      y1 - y,
			      x2 - x1,
			      y2 - y1,
			      0 * 64,
			      360 * 64);
	}

	if (re->outline_set) {
		if (re->outline_stipple)
			gossip_canvas_set_stipple_origin (item->canvas, re->outline_gc);

		gdk_draw_arc (drawable,
			      re->outline_gc,
			      FALSE,
			      x1 - x,
			      y1 - y,
			      x2 - x1,
			      y2 - y1,
			      0 * 64,
			      360 * 64);
	}
}

static double
gossip_canvas_ellipse_point (GossipCanvasItem *item, double x, double y, int cx, int cy, GossipCanvasItem **actual_item)
{
	GossipCanvasRE *re;
	double dx, dy;
	double scaled_dist;
	double outline_dist;
	double center_dist;
	double width;
	double a, b;
	double diamx, diamy;

	re = GOSSIP_CANVAS_RE (item);

	*actual_item = item;

	if (re->outline_set) {
		if (re->width_pixels)
			width = re->width / item->canvas->pixels_per_unit;
		else
			width = re->width;
	} else
		width = 0.0;

	/* Compute the distance between the center of the ellipse and the point, with the ellipse
	 * considered as being scaled to a circle.
	 */

	dx = x - (re->x1 + re->x2) / 2.0;
	dy = y - (re->y1 + re->y2) / 2.0;
	center_dist = sqrt (dx * dx + dy * dy);

	a = dx / ((re->x2 + width - re->x1) / 2.0);
	b = dy / ((re->y2 + width - re->y1) / 2.0);
	scaled_dist = sqrt (a * a + b * b);

	/* If the scaled distance is greater than 1, then we are outside.  Compute the distance from
	 * the point to the edge of the circle, then scale back to the original un-scaled coordinate
	 * system.
	 */

	if (scaled_dist > 1.0)
		return (center_dist / scaled_dist) * (scaled_dist - 1.0);

	/* We are inside the outer edge of the ellipse.  If it is filled, then we are "inside".
	 * Otherwise, do the same computation as above, but also check whether we are inside the
	 * outline.
	 */

	if (re->fill_set || !re->outline_set)
		return 0.0;

	if (scaled_dist > GOSSIP_CANVAS_EPSILON)
		outline_dist = (center_dist / scaled_dist) * (1.0 - scaled_dist) - width;
	else {
		/* Handle very small distance */

		diamx = re->x2 - re->x1;
		diamy = re->y2 - re->y1;

		if (diamx < diamy)
			outline_dist = (diamx - width) / 2.0;
		else
			outline_dist = (diamy - width) / 2.0;
	}

	if (outline_dist < 0.0)
		return 0.0;

	return outline_dist;
}

#define N_PTS 126

#if 0
static void
gossip_canvas_gen_ellipse (ArtVpath *vpath, double x0, double y0,
			  double x1, double y1)
{
	int i;

	for (i = 0; i < N_PTS + 1; i++) {
		double th;

		th = (2 * M_PI * i) / N_PTS;
		vpath[i].code = i == 0 ? ART_MOVETO : ART_LINETO;
		vpath[i].x = (x0 + x1) * 0.5 + (x1 - x0) * 0.5 * cos (th);
		vpath[i].y = (y0 + y1) * 0.5 - (y1 - y0) * 0.5 * sin (th);
	}
}
#endif

static void
gossip_canvas_ellipse_update (GossipCanvasItem *item, double affine[6], gint flags)
{
	GossipCanvasRE *re;
#if 0
	ArtVpath vpath[N_PTS + N_PTS + 3];
	ArtVpath *vpath2;
#endif
	double x0, y0, x1, y1;
	int i;

#ifdef VERBOSE
	g_print ("gossip_canvas_rect_update item %x\n", item);
#endif

	gossip_canvas_re_update_shared (item, affine, flags);
	re = GOSSIP_CANVAS_RE (item);

#if 0
	if (item->canvas->aa) {

#ifdef VERBOSE
		{
			char str[128];

			art_affine_to_string (str, affine);
			g_print ("g_c_r_e affine = %s\n", str);
		}
		g_print ("item %x (%g, %g) - (%g, %g)\n",
			 item,
			 re->x1, re->y1, re->x2, re->y2);
#endif

		if (re->fill_set) {
			gossip_canvas_gen_ellipse (vpath, re->x1, re->y1, re->x2, re->y2);
			vpath[N_PTS + 1].code = ART_END;
			vpath[N_PTS + 1].x = 0;
			vpath[N_PTS + 1].y = 0;

			vpath2 = art_vpath_affine_transform (vpath, affine);

			gossip_canvas_item_update_svp_clip (item, &re->fill_svp, art_svp_from_vpath (vpath2), clip_path);
			art_free (vpath2);
		} else
			gossip_canvas_item_update_svp (item, &re->fill_svp, NULL);

		if (re->outline_set) {
			double halfwidth;

			if (re->width_pixels)
				halfwidth = (re->width / item->canvas->pixels_per_unit) * 0.5;
			else
				halfwidth = re->width * 0.5;

			if (halfwidth < 0.25)
				halfwidth = 0.25;

			i = 0;
			gossip_canvas_gen_ellipse (vpath + i,
						  re->x1 - halfwidth, re->y1 - halfwidth,
						  re->x2 + halfwidth, re->y2 + halfwidth);
			i = N_PTS + 1;
			if (re->x2 - halfwidth > re->x1 + halfwidth &&
			    re->y2 - halfwidth > re->y1 + halfwidth) {
				gossip_canvas_gen_ellipse (vpath + i,
							  re->x1 + halfwidth, re->y2 - halfwidth,
							  re->x2 - halfwidth, re->y1 + halfwidth);
				i += N_PTS + 1;
			}
			vpath[i].code = ART_END;
			vpath[i].x = 0;
			vpath[i].y = 0;

			vpath2 = art_vpath_affine_transform (vpath, affine);

			gossip_canvas_item_update_svp_clip (item, &re->outline_svp, art_svp_from_vpath (vpath2), clip_path);
			art_free (vpath2);
		} else
			gossip_canvas_item_update_svp (item, &re->outline_svp, NULL);
	} else 
#endif
	  {
		/* xlib rendering - just update the bbox */
		get_bounds (re, &x0, &y0, &x1, &y1);
		gossip_canvas_update_bbox (item, x0, y0, x1, y1);
	}

}
