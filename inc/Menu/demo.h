#ifndef DEMO_H
#define DEMO_H

#include "nanovg.h"

#ifdef __cplusplus
extern "C" {
#endif

struct MenuData {
	int fontNormal, fontBold, fontIcons, fontEmoji;
	int images[12];
};
typedef struct MenuData MenuData;

int loadMenuData(NVGcontext* vg, MenuData* data);
void freeMenuData(NVGcontext* vg, MenuData* data);
void renderDemo(NVGcontext* vg, float mx, float my, float width, float height, float t, int blowup, MenuData* data);

void saveScreenShot(int w, int h, int premult, const char* name);

#ifdef __cplusplus
}
#endif

#endif // DEMO_H
