#include <tizen.h>
#include "mohface.h"

typedef struct appdata {
	Evas_Object *win;
	Evas_Object *conform;
	Evas_Object *label;
} appdata_s;

#define TEXT_BUF_SIZE 256
//#define ICON_DIR "shared/res"

static void
update_watch(appdata_s *ad, watch_time_h watch_time, int ambient)
{

	char watch_text[TEXT_BUF_SIZE];
	int hour24, minute, second;
//	   Evas_Object *layout, *img;
//	   char imgbuf[PATH_MAX];
//	   int x, y, w, h;
//
//	if (watch_time == NULL)
//		return;
//
//	   layout = elm_layout_add(ad->win);
//	      x = 0;
//	      y = 0;
//	      w = 360;
//	      h = 360;
//
//
//	      img = elm_image_add(layout);
	watch_time_get_hour24(watch_time, &hour24);
	watch_time_get_minute(watch_time, &minute);
	watch_time_get_second(watch_time, &second);
//
//	if (!ambient) {
//		snprintf(watch_text, TEXT_BUF_SIZE, "<align=center>Hello Watch<br/>%02d:%02d:%02d</align>",
//			hour24, minute, second);
//		snprintf(imgbuf, sizeof(imgbuf), "%s/mohface.png", ICON_DIR);
//	} else {
//		snprintf(watch_text, TEXT_BUF_SIZE, "<align=center>Hello Watch<br/>%02d:%02d</align>",
//			hour24, minute);
//		snprintf(imgbuf, sizeof(imgbuf), "%s/mohface_ambient.png", ICON_DIR);
//	}
//
//         elm_image_file_set(img, imgbuf, NULL);
//
//         evas_object_resize(img, w, h);
//         evas_object_move(img, x, y);
//         evas_object_show(img);
//
//         elm_object_text_set(ad->label, watch_text);

	    Evas_Object *main_box = elm_box_add(ad->conform);
	    evas_object_size_hint_weight_set(main_box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	    evas_object_size_hint_align_set(main_box, EVAS_HINT_FILL, EVAS_HINT_FILL);
	    evas_object_show(main_box);

	    /* Creating a background */
	    Evas_Object *bg = elm_bg_add(main_box);
	    evas_object_size_hint_weight_set(bg, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	    evas_object_size_hint_align_set(bg, EVAS_HINT_FILL, EVAS_HINT_FILL);

	    /* Use red color for background */
	    //elm_bg_color_set(bg, 0xFF, 0x00, 0x00);
	    /* Set a file on the disk as background image */
	    elm_bg_file_set(bg, "/opt/usr/home/owner/apps_rw/com.github.rlegendi.mohface/shared/res/mohface.png", NULL);
	    /* Set an edje group as background image */
	    //elm_bg_file_set(bg, "/path/to/the/edje", "edje_group");

	    elm_bg_option_set(bg, ELM_BG_OPTION_STRETCH);
	    evas_object_show(bg);

	    /* Title Label*/
	    Evas_Object *label = elm_label_add(main_box);
	    snprintf(watch_text, TEXT_BUF_SIZE, "<align=center>%02d:%02d:%02d</align>",
	    			hour24, minute, second);
	    elm_object_text_set(label, watch_text);
//	    evas_object_move(label, 100, 200);
	    evas_object_show(label);

	    elm_object_part_content_set(bg, "overlay", label);
	    elm_box_pack_end(main_box, bg);

	    elm_object_content_set(ad->conform, main_box);
}

static void
create_base_gui(appdata_s *ad, int width, int height)
{
	int ret;
	watch_time_h watch_time = NULL;

	/* Window */
	ret = watch_app_get_elm_win(&ad->win);
	if (ret != APP_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "failed to get window. err = %d", ret);
		return;
	}

	evas_object_resize(ad->win, width, height);

	/* Conformant */
	ad->conform = elm_conformant_add(ad->win);
	evas_object_size_hint_weight_set(ad->conform, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_win_resize_object_add(ad->win, ad->conform);
	evas_object_show(ad->conform);

	/* Label*/
	ad->label = elm_label_add(ad->conform);
	evas_object_resize(ad->label, width, height / 3);
	evas_object_move(ad->label, 0, height / 3);
	evas_object_show(ad->label);

	ret = watch_time_get_current_time(&watch_time);
	if (ret != APP_ERROR_NONE)
		dlog_print(DLOG_ERROR, LOG_TAG, "failed to get current time. err = %d", ret);

	update_watch(ad, watch_time, 0);
	watch_time_delete(watch_time);

	/* Show window after base gui is set up */
	evas_object_show(ad->win);
}

/* Hook to take necessary actions before main event loop starts
	Initialize UI resources and application's data
	If this function returns true, the main loop of application starts
	If this function returns false, the application is terminated */
static bool
app_create(int width, int height, void *data)
{
	appdata_s *ad = data;

	create_base_gui(ad, width, height);

	return true;
}

/* Handle the launch request. */
static void
app_control(app_control_h app_control, void *data)
{

}

/* Take necessary actions when application becomes invisible. */
static void
app_pause(void *data)
{

}

/* Take necessary actions when application becomes visible. */
static void
app_resume(void *data)
{

}

/* Release all resources. */
static void
app_terminate(void *data)
{

}

/* Called at each second while your app is visible. Update watch UI. */
static void
app_time_tick(watch_time_h watch_time, void *data)
{

	appdata_s *ad = data;
	update_watch(ad, watch_time, 0);
}


/* Called at each minute while the device is in ambient mode. Update watch UI. */
static void
app_ambient_tick(watch_time_h watch_time, void *data)
{
	appdata_s *ad = data;
	update_watch(ad, watch_time, 1);
}

/* Update your watch UI to conform to the ambient mode */
static void
app_ambient_changed(bool ambient_mode, void *data)
{

}

/*APP_EVENT_LANGUAGE_CHANGED*/
static void
watch_app_lang_changed(app_event_info_h event_info, void *user_data)
{

	char *locale = NULL;
	app_event_get_language(event_info, &locale);
	elm_language_set(locale);
	free(locale);
	return;
}

/*APP_EVENT_REGION_FORMAT_CHANGED*/
static void
watch_app_region_changed(app_event_info_h event_info, void *user_data)
{

}

int
main(int argc, char *argv[])
{
	appdata_s ad = {0,};
	int ret = 0;

	watch_app_lifecycle_callback_s event_callback = {0,};
	app_event_handler_h handlers[5] = {NULL, };

	event_callback.create = app_create;
	event_callback.terminate = app_terminate;
	event_callback.pause = app_pause;
	event_callback.resume = app_resume;
	event_callback.app_control = app_control;
	event_callback.time_tick = app_time_tick;
	event_callback.ambient_tick = app_ambient_tick;
	event_callback.ambient_changed = app_ambient_changed;

	watch_app_add_event_handler(&handlers[APP_EVENT_LANGUAGE_CHANGED],
		APP_EVENT_LANGUAGE_CHANGED, watch_app_lang_changed, &ad);
	watch_app_add_event_handler(&handlers[APP_EVENT_REGION_FORMAT_CHANGED],
		APP_EVENT_REGION_FORMAT_CHANGED, watch_app_region_changed, &ad);

	ret = watch_app_main(argc, argv, &event_callback, &ad);
	if (ret != APP_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "watch_app_main() is failed. err = %d", ret);
	}

	return ret;
}

