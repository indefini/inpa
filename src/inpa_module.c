#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include <stdio.h>

#include <Ecore.h>
#include <Ecore_IMF.h>

#include "inpa_imcontext.h"

static const Ecore_IMF_Context_Info inpa_im_info = {
    "inpa",
    "Inpa (no meaning)",
    "*",
    NULL,
    0
};

static Ecore_IMF_Context_Class inpa_imf_class = {
    ecore_imf_context_inpa_add,                    /* add */
    ecore_imf_context_inpa_del,                    /* del */
    NULL,//ecore_imf_context_ibus_client_window_set,      /* client_window_set */
    NULL,//ecore_imf_context_ibus_client_canvas_set,      /* client_canvas_set */
    inpa_show,//NULL,                                          /* input_panel_show */
    inpa_hide,//NULL,                                          /* input_panel_hide */
    NULL,//ecore_imf_context_ibus_preedit_string_get,     /* get_preedit_string */
    inpa_focus_in,//ecore_imf_context_ibus_focus_in,               /* focus_in */
    inpa_focus_out,//ecore_imf_context_ibus_focus_out,              /* focus_out */
    NULL,//ecore_imf_context_ibus_reset,                  /* reset */
    NULL,                                          /* cursor_position_set */
    NULL,//ecore_imf_context_ibus_use_preedit_set,        /* use_preedit_set */
    NULL,                                          /* input_mode_set */
    NULL,//ecore_imf_context_ibus_filter_event,           /* filter_event */
    NULL,//ecore_imf_context_ibus_preedit_string_with_attributes_get,  /* preedit_string_with_attribute_get */
    NULL,                                          /* prediction_allow_set */
    NULL,                                          /* autocapital_type_set */
    inpa_control_show,                                          /* control panel show */
    inpa_control_hide,                                          /* control panel hide */
    NULL,                                          /* input_panel_layout_set */
    NULL,                                          /* ecore_imf_context_ibus_input_panel_layout_get, */
    NULL,                                          /* ecore_imf_context_ibus_input_panel_language_set, */
    NULL,                                          /* ecore_imf_context_ibus_input_panel_language_get, */
    NULL,//ecore_imf_context_ibus_cursor_location_set,    /* cursor_location_set */
    NULL,                                          /* input_panel_imdata_set */
    NULL,                                          /* input_panel_imdata_get */
    NULL,                                          /* input_panel_return_key_type_set */
    NULL,                                          /* input_panel_return_key_disabled_set */
    NULL,                                          /* input_panel_caps_lock_mode_set */
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL
};

static Ecore_IMF_Context *im_module_create (void);
static Ecore_IMF_Context *im_module_exit (void);

static Eina_Bool
im_module_init(void)
{
   const char *s;

   if (!getenv("DISPLAY")) return EINA_FALSE;
   if ((s = getenv("ELM_DISPLAY")))
     {
        if (strcmp(s, "x11")) return EINA_FALSE;
     }
   ecore_main_loop_glib_integrate();
    //ibus_init();
    ecore_imf_module_register(&inpa_im_info, im_module_create, im_module_exit);

    return EINA_TRUE;
}

static void im_module_shutdown(void)
{
}

static Ecore_IMF_Context *
im_module_exit(void)
{
    return NULL;
}

static Ecore_IMF_Context *
im_module_create(void)
{
    Ecore_IMF_Context *ctx = NULL;
    InpaIMContext *ctxd = NULL;

    ctxd = ecore_imf_context_inpa_new();
    if (!ctxd)
      {
         return NULL;
      }

    ctx = ecore_imf_context_new(&inpa_imf_class);
    if (!ctx)
      {
       //  free(ctxd);
         return NULL;
      }

    ecore_imf_context_data_set(ctx, ctxd);

    return ctx;
}

EINA_MODULE_INIT(im_module_init);
EINA_MODULE_SHUTDOWN(im_module_shutdown);
