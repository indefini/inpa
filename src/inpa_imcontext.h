#ifndef __INPA_IM_CONTEXT_H_
#define __INPA_IM_CONTEXT_H_

#include <Ecore_IMF.h>

typedef struct _InpaIMContext InpaIMContext;

EAPI void ecore_imf_context_inpa_add(Ecore_IMF_Context *ctx);

EAPI void ecore_imf_context_inpa_del(Ecore_IMF_Context *ctx);

EAPI void inpa_show(Ecore_IMF_Context *ctx);
EAPI void inpa_hide(Ecore_IMF_Context *ctx);

EAPI void inpa_focus_in(Ecore_IMF_Context *ctx);
EAPI void inpa_focus_out(Ecore_IMF_Context *ctx);

EAPI void inpa_control_show(Ecore_IMF_Context *ctx);
EAPI void inpa_control_hide(Ecore_IMF_Context *ctx);

InpaIMContext *ecore_imf_context_inpa_new(void);

#endif
