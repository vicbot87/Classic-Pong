#include <string.h>

//#include "toolbox.h"
#include "input.h"
#include "tonc_core.h"
#include "tonc_video.h"

#define BTN_PAL  5
#define CLR_UP   RGB15(27,27,29)

#define BALL_SIZE 10

#define SEG_SPACE 1
#define SEG_WIDTH 3
#define TOT_SEG_WIDTH 10

// top left corner:
#define INIT_X  108
#define INIT_Y  72

void seven_seg(u8 x, u8 y, u8 val, COLOR clr) {
    // a
    u8 ax = x + SEG_WIDTH + SEG_SPACE;
    u8 ay = y;
    // b
    u8 bx = x + 2 * SEG_SPACE + SEG_WIDTH + TOT_SEG_WIDTH;
    u8 by = y + SEG_WIDTH + SEG_SPACE;
    // c
    u8 cx = bx;
    u8 cy = by + 2 * SEG_SPACE + SEG_WIDTH + TOT_SEG_WIDTH;
    // d
    u8 dx = ax;
    u8 dy = ay + 2 * SEG_WIDTH + 4 * SEG_SPACE + 2 * TOT_SEG_WIDTH;
    // e
    u8 ex = x;
    u8 ey = ay + 3 * SEG_SPACE + 2 * SEG_WIDTH + TOT_SEG_WIDTH;
    // f
    u8 fx = x;
    u8 fy = ay + SEG_SPACE + SEG_WIDTH;
    // g
    u8 gx = ax;
    u8 gy = ay + 2 * SEG_SPACE + SEG_WIDTH + TOT_SEG_WIDTH;

    if (0x40 & val)
        m3_rect(ax, ay, ax + TOT_SEG_WIDTH, ay + SEG_WIDTH, clr);
    if (0x20 & val)
        m3_rect(bx, by, bx + SEG_WIDTH, by + TOT_SEG_WIDTH, clr);
    if (0x10 & val)
        m3_rect(cx, cy, cx + SEG_WIDTH, cy + TOT_SEG_WIDTH, clr);
    if (0x8 & val)
        m3_rect(dx, dy, dx + TOT_SEG_WIDTH, dy + SEG_WIDTH, clr);
    if (0x4 & val)
        m3_rect(ex, ey, ex + SEG_WIDTH, ey + TOT_SEG_WIDTH, clr);
    if (0x2 & val)
        m3_rect(fx, fy, fx + SEG_WIDTH, fy + TOT_SEG_WIDTH, clr);
    if (0x1 & val)
        m3_rect(gx, gy, gx + TOT_SEG_WIDTH, gy + SEG_WIDTH, clr);
}

int main()
{
    int frame=0;

    REG_DISPCNT= DCNT_MODE3 | DCNT_BG2;

    u8 xcoord = INIT_X;
    u8 ycoord = INIT_Y;
    u8 xchange = 1;
    u8 ychange = 1;


    while(1)
    {
        // Draw before screen refresh
        m3_rect(xcoord, ycoord, xcoord + BALL_SIZE, ycoord + BALL_SIZE, CLR_LIME);

        vid_vsync();
        if (frame % 4 != 0) {frame++; continue;} // Slow down redraws

        // Actions

        key_poll();
        if (key_hit(KEY_LEFT)) {
            xchange = -1;
        }
        if (key_hit(KEY_RIGHT)) {
            xchange = 1;
        }
        if (key_hit(KEY_UP)) {
            ychange = -1;
        }
        if (key_hit(KEY_DOWN)) {
            ychange = 1;
        }

        // Make sure the ball stays in bounds

        if (ycoord >= M3_HEIGHT - BALL_SIZE) {
            ychange = -1;
        } else if (ycoord == 0) {
            ychange = 1;
        }
        if (xcoord >= M3_WIDTH - BALL_SIZE) {
            xchange = -1;
        } else if (xcoord == 0) {
            xchange = 1;
        }

        // Draw after screen refresh
        m3_fill(CLR_BLACK);

        // updates
        xcoord += xchange;
        ycoord += ychange;
        frame++;
    }

    return 0;
}
