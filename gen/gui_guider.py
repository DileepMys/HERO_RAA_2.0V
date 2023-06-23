# Copyright 2021 NXP
# SPDX-License-Identifier: MIT

import SDL
import utime as time
import usys as sys
import lvgl as lv
import lodepng as png
import ustruct

lv.init()
SDL.init(w=240,h=320)

# Register SDL display driver.
disp_buf1 = lv.disp_draw_buf_t()
buf1_1 = bytearray(240*10)
disp_buf1.init(buf1_1, None, len(buf1_1)//4)
disp_drv = lv.disp_drv_t()
disp_drv.init()
disp_drv.draw_buf = disp_buf1
disp_drv.flush_cb = SDL.monitor_flush
disp_drv.hor_res = 240
disp_drv.ver_res = 320
disp_drv.register()

# Regsiter SDL mouse driver
indev_drv = lv.indev_drv_t()
indev_drv.init() 
indev_drv.type = lv.INDEV_TYPE.POINTER
indev_drv.read_cb = SDL.mouse_read
indev_drv.register()

# Below: Taken from https://github.com/lvgl/lv_binding_micropython/blob/master/driver/js/imagetools.py#L22-L94

COLOR_SIZE = lv.color_t.__SIZE__
COLOR_IS_SWAPPED = hasattr(lv.color_t().ch,'green_h')

class lodepng_error(RuntimeError):
    def __init__(self, err):
        if type(err) is int:
            super().__init__(png.error_text(err))
        else:
            super().__init__(err)

# Parse PNG file header
# Taken from https://github.com/shibukawa/imagesize_py/blob/ffef30c1a4715c5acf90e8945ceb77f4a2ed2d45/imagesize.py#L63-L85

def get_png_info(decoder, src, header):
    # Only handle variable image types

    if lv.img.src_get_type(src) != lv.img.SRC.VARIABLE:
        return lv.RES.INV

    data = lv.img_dsc_t.__cast__(src).data
    if data == None:
        return lv.RES.INV

    png_header = bytes(data.__dereference__(24))

    if png_header.startswith(b'\211PNG\r\n\032\n'):
        if png_header[12:16] == b'IHDR':
            start = 16
        # Maybe this is for an older PNG version.
        else:
            start = 8
        try:
            width, height = ustruct.unpack(">LL", png_header[start:start+8])
        except ustruct.error:
            return lv.RES.INV
    else:
        return lv.RES.INV

    header.always_zero = 0
    header.w = width
    header.h = height
    header.cf = lv.img.CF.TRUE_COLOR_ALPHA

    return lv.RES.OK

def convert_rgba8888_to_bgra8888(img_view):
    for i in range(0, len(img_view), lv.color_t.__SIZE__):
        ch = lv.color_t.__cast__(img_view[i:i]).ch
        ch.red, ch.blue = ch.blue, ch.red

# Read and parse PNG file

def open_png(decoder, dsc):
    img_dsc = lv.img_dsc_t.__cast__(dsc.src)
    png_data = img_dsc.data
    png_size = img_dsc.data_size
    png_decoded = png.C_Pointer()
    png_width = png.C_Pointer()
    png_height = png.C_Pointer()
    error = png.decode32(png_decoded, png_width, png_height, png_data, png_size)
    if error:
        raise lodepng_error(error)
    img_size = png_width.int_val * png_height.int_val * 4
    img_data = png_decoded.ptr_val
    img_view = img_data.__dereference__(img_size)

    if COLOR_SIZE == 4:
        convert_rgba8888_to_bgra8888(img_view)
    else:
        raise lodepng_error("Error: Color mode not supported yet!")

    dsc.img_data = img_data
    return lv.RES.OK

# Above: Taken from https://github.com/lvgl/lv_binding_micropython/blob/master/driver/js/imagetools.py#L22-L94

decoder = lv.img.decoder_create()
decoder.info_cb = get_png_info
decoder.open_cb = open_png

def anim_x_cb(obj, v):
    obj.set_x(v)

def anim_y_cb(obj, v):
    obj.set_y(v)

def ta_event_cb(e,kb):
    code = e.get_code()
    ta = e.get_target()
    if code == lv.EVENT.FOCUSED:
        kb.set_textarea(ta)
        kb.clear_flag(lv.obj.FLAG.HIDDEN)

    if code == lv.EVENT.DEFOCUSED:
        kb.set_textarea(None)
        kb.add_flag(lv.obj.FLAG.HIDDEN)


Main_Screen = lv.obj()
# create style style_main_screen_main_main_default
style_main_screen_main_main_default = lv.style_t()
style_main_screen_main_main_default.init()
style_main_screen_main_main_default.set_bg_color(lv.color_make(0x00,0x00,0x00))
style_main_screen_main_main_default.set_bg_opa(255)

# add style for Main_Screen
Main_Screen.add_style(style_main_screen_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

Main_Screen_Welcome_img = lv.img(Main_Screen)
Main_Screen_Welcome_img.set_pos(0,0)
Main_Screen_Welcome_img.set_size(240,320)
Main_Screen_Welcome_img.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-369897119.png','rb') as f:
        Main_Screen_Welcome_img_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-369897119.png')
    sys.exit()

Main_Screen_Welcome_img_img = lv.img_dsc_t({
  'data_size': len(Main_Screen_Welcome_img_img_data),
  'header': {'always_zero': 0, 'w': 240, 'h': 320, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': Main_Screen_Welcome_img_img_data
})

Main_Screen_Welcome_img.set_src(Main_Screen_Welcome_img_img)
Main_Screen_Welcome_img.set_pivot(0,0)
Main_Screen_Welcome_img.set_angle(0)
# create style style_main_screen_welcome_img_main_main_default
style_main_screen_welcome_img_main_main_default = lv.style_t()
style_main_screen_welcome_img_main_main_default.init()
style_main_screen_welcome_img_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_main_screen_welcome_img_main_main_default.set_img_recolor_opa(0)
style_main_screen_welcome_img_main_main_default.set_img_opa(255)

# add style for Main_Screen_Welcome_img
Main_Screen_Welcome_img.add_style(style_main_screen_welcome_img_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen = lv.obj()
# create style style_screen_main_main_default
style_screen_main_main_default = lv.style_t()
style_screen_main_main_default.init()
style_screen_main_main_default.set_bg_color(lv.color_make(0x00,0x00,0x00))
style_screen_main_main_default.set_bg_opa(255)

# add style for screen
screen.add_style(style_screen_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_skin = lv.img(screen)
screen_skin.set_pos(0,0)
screen_skin.set_size(240,320)
screen_skin.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp83675671.png','rb') as f:
        screen_skin_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp83675671.png')
    sys.exit()

screen_skin_img = lv.img_dsc_t({
  'data_size': len(screen_skin_img_data),
  'header': {'always_zero': 0, 'w': 240, 'h': 320, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_skin_img_data
})

screen_skin.set_src(screen_skin_img)
screen_skin.set_pivot(0,0)
screen_skin.set_angle(0)
# create style style_screen_skin_main_main_default
style_screen_skin_main_main_default = lv.style_t()
style_screen_skin_main_main_default.init()
style_screen_skin_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_skin_main_main_default.set_img_recolor_opa(0)
style_screen_skin_main_main_default.set_img_opa(255)

# add style for screen_skin
screen_skin.add_style(style_screen_skin_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_Circ = lv.img(screen)
screen_Circ.set_pos(7,47)
screen_Circ.set_size(226,226)
screen_Circ.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-480540445.png','rb') as f:
        screen_Circ_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-480540445.png')
    sys.exit()

screen_Circ_img = lv.img_dsc_t({
  'data_size': len(screen_Circ_img_data),
  'header': {'always_zero': 0, 'w': 226, 'h': 226, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_Circ_img_data
})

screen_Circ.set_src(screen_Circ_img)
screen_Circ.set_pivot(0,0)
screen_Circ.set_angle(0)
# create style style_screen_circ_main_main_default
style_screen_circ_main_main_default = lv.style_t()
style_screen_circ_main_main_default.init()
style_screen_circ_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_circ_main_main_default.set_img_recolor_opa(0)
style_screen_circ_main_main_default.set_img_opa(0)

# add style for screen_Circ
screen_Circ.add_style(style_screen_circ_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TripA = lv.img(screen)
screen_TripA.set_pos(105,252)
screen_TripA.set_size(30,30)
screen_TripA.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp741552124.png','rb') as f:
        screen_TripA_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp741552124.png')
    sys.exit()

screen_TripA_img = lv.img_dsc_t({
  'data_size': len(screen_TripA_img_data),
  'header': {'always_zero': 0, 'w': 30, 'h': 30, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TripA_img_data
})

screen_TripA.set_src(screen_TripA_img)
screen_TripA.set_pivot(0,0)
screen_TripA.set_angle(0)
# create style style_screen_tripa_main_main_default
style_screen_tripa_main_main_default = lv.style_t()
style_screen_tripa_main_main_default.init()
style_screen_tripa_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tripa_main_main_default.set_img_recolor_opa(0)
style_screen_tripa_main_main_default.set_img_opa(255)

# add style for screen_TripA
screen_TripA.add_style(style_screen_tripa_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_FogLampTT = lv.imgbtn(screen)
screen_FogLampTT.set_pos(10,12)
screen_FogLampTT.set_size(24,20)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-552738788.png','rb') as f:
        screen_FogLampTT_imgReleased_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-552738788.png')
    sys.exit()

screen_FogLampTT_imgReleased = lv.img_dsc_t({
  'data_size': len(screen_FogLampTT_imgReleased_data),
  'header': {'always_zero': 0, 'w': 24, 'h': 20, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_FogLampTT_imgReleased_data
})
screen_FogLampTT.set_src(lv.imgbtn.STATE.RELEASED, screen_FogLampTT_imgReleased, None, None)

try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp193804431.png','rb') as f:
        screen_FogLampTT_imgPressed_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp193804431.png')
    sys.exit()

screen_FogLampTT_imgPressed = lv.img_dsc_t({
  'data_size': len(screen_FogLampTT_imgPressed_data),
  'header': {'always_zero': 0, 'w': 24, 'h': 20, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_FogLampTT_imgPressed_data
})
screen_FogLampTT.set_src(lv.imgbtn.STATE.PRESSED, screen_FogLampTT_imgPressed, None, None)




screen_FogLampTT.add_flag(lv.obj.FLAG.CHECKABLE)
# create style style_screen_foglamptt_main_main_default
style_screen_foglamptt_main_main_default = lv.style_t()
style_screen_foglamptt_main_main_default.init()
style_screen_foglamptt_main_main_default.set_text_color(lv.color_make(0x00,0x00,0x00))
try:
    style_screen_foglamptt_main_main_default.set_text_font(lv.font_simsun_12)
except AttributeError:
    try:
        style_screen_foglamptt_main_main_default.set_text_font(lv.font_montserrat_12)
    except AttributeError:
        style_screen_foglamptt_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_foglamptt_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_foglamptt_main_main_default.set_img_recolor_opa(0)
style_screen_foglamptt_main_main_default.set_img_opa(255)

# add style for screen_FogLampTT
screen_FogLampTT.add_style(style_screen_foglamptt_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_screen_foglamptt_main_main_pressed
style_screen_foglamptt_main_main_pressed = lv.style_t()
style_screen_foglamptt_main_main_pressed.init()
style_screen_foglamptt_main_main_pressed.set_text_color(lv.color_make(0xFF,0x33,0xFF))
try:
    style_screen_foglamptt_main_main_pressed.set_text_font(lv.font_simsun_16)
except AttributeError:
    try:
        style_screen_foglamptt_main_main_pressed.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_screen_foglamptt_main_main_pressed.set_text_font(lv.font_montserrat_16)
style_screen_foglamptt_main_main_pressed.set_img_recolor(lv.color_make(0x00,0x00,0x00))
style_screen_foglamptt_main_main_pressed.set_img_recolor_opa(0)

# add style for screen_FogLampTT
screen_FogLampTT.add_style(style_screen_foglamptt_main_main_pressed, lv.PART.MAIN|lv.STATE.PRESSED)

# create style style_screen_foglamptt_main_main_checked
style_screen_foglamptt_main_main_checked = lv.style_t()
style_screen_foglamptt_main_main_checked.init()
style_screen_foglamptt_main_main_checked.set_text_color(lv.color_make(0xFF,0x33,0xFF))
try:
    style_screen_foglamptt_main_main_checked.set_text_font(lv.font_simsun_16)
except AttributeError:
    try:
        style_screen_foglamptt_main_main_checked.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_screen_foglamptt_main_main_checked.set_text_font(lv.font_montserrat_16)
style_screen_foglamptt_main_main_checked.set_img_recolor(lv.color_make(0x00,0x00,0x00))
style_screen_foglamptt_main_main_checked.set_img_recolor_opa(0)

# add style for screen_FogLampTT
screen_FogLampTT.add_style(style_screen_foglamptt_main_main_checked, lv.PART.MAIN|lv.STATE.CHECKED)

screen_imgEngineTT = lv.imgbtn(screen)
screen_imgEngineTT.set_pos(205,13)
screen_imgEngineTT.set_size(25,17)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1283435164.png','rb') as f:
        screen_imgEngineTT_imgReleased_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1283435164.png')
    sys.exit()

screen_imgEngineTT_imgReleased = lv.img_dsc_t({
  'data_size': len(screen_imgEngineTT_imgReleased_data),
  'header': {'always_zero': 0, 'w': 25, 'h': 17, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_imgEngineTT_imgReleased_data
})
screen_imgEngineTT.set_src(lv.imgbtn.STATE.RELEASED, screen_imgEngineTT_imgReleased, None, None)

try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp1229638200.png','rb') as f:
        screen_imgEngineTT_imgPressed_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp1229638200.png')
    sys.exit()

screen_imgEngineTT_imgPressed = lv.img_dsc_t({
  'data_size': len(screen_imgEngineTT_imgPressed_data),
  'header': {'always_zero': 0, 'w': 25, 'h': 17, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_imgEngineTT_imgPressed_data
})
screen_imgEngineTT.set_src(lv.imgbtn.STATE.PRESSED, screen_imgEngineTT_imgPressed, None, None)




screen_imgEngineTT.add_flag(lv.obj.FLAG.CHECKABLE)
# create style style_screen_imgenginett_main_main_default
style_screen_imgenginett_main_main_default = lv.style_t()
style_screen_imgenginett_main_main_default.init()
style_screen_imgenginett_main_main_default.set_text_color(lv.color_make(0x00,0x00,0x00))
try:
    style_screen_imgenginett_main_main_default.set_text_font(lv.font_simsun_12)
except AttributeError:
    try:
        style_screen_imgenginett_main_main_default.set_text_font(lv.font_montserrat_12)
    except AttributeError:
        style_screen_imgenginett_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_imgenginett_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_imgenginett_main_main_default.set_img_recolor_opa(0)
style_screen_imgenginett_main_main_default.set_img_opa(255)

# add style for screen_imgEngineTT
screen_imgEngineTT.add_style(style_screen_imgenginett_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_screen_imgenginett_main_main_pressed
style_screen_imgenginett_main_main_pressed = lv.style_t()
style_screen_imgenginett_main_main_pressed.init()
style_screen_imgenginett_main_main_pressed.set_text_color(lv.color_make(0xFF,0x33,0xFF))
try:
    style_screen_imgenginett_main_main_pressed.set_text_font(lv.font_simsun_16)
except AttributeError:
    try:
        style_screen_imgenginett_main_main_pressed.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_screen_imgenginett_main_main_pressed.set_text_font(lv.font_montserrat_16)
style_screen_imgenginett_main_main_pressed.set_img_recolor(lv.color_make(0x00,0x00,0x00))
style_screen_imgenginett_main_main_pressed.set_img_recolor_opa(0)

# add style for screen_imgEngineTT
screen_imgEngineTT.add_style(style_screen_imgenginett_main_main_pressed, lv.PART.MAIN|lv.STATE.PRESSED)

# create style style_screen_imgenginett_main_main_checked
style_screen_imgenginett_main_main_checked = lv.style_t()
style_screen_imgenginett_main_main_checked.init()
style_screen_imgenginett_main_main_checked.set_text_color(lv.color_make(0xFF,0x33,0xFF))
try:
    style_screen_imgenginett_main_main_checked.set_text_font(lv.font_simsun_16)
except AttributeError:
    try:
        style_screen_imgenginett_main_main_checked.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_screen_imgenginett_main_main_checked.set_text_font(lv.font_montserrat_16)
style_screen_imgenginett_main_main_checked.set_img_recolor(lv.color_make(0x00,0x00,0x00))
style_screen_imgenginett_main_main_checked.set_img_recolor_opa(0)

# add style for screen_imgEngineTT
screen_imgEngineTT.add_style(style_screen_imgenginett_main_main_checked, lv.PART.MAIN|lv.STATE.CHECKED)

screen_Trip_blank = lv.img(screen)
screen_Trip_blank.set_pos(105,255)
screen_Trip_blank.set_size(30,30)
screen_Trip_blank.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp777785504.png','rb') as f:
        screen_Trip_blank_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp777785504.png')
    sys.exit()

screen_Trip_blank_img = lv.img_dsc_t({
  'data_size': len(screen_Trip_blank_img_data),
  'header': {'always_zero': 0, 'w': 30, 'h': 30, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_Trip_blank_img_data
})

screen_Trip_blank.set_src(screen_Trip_blank_img)
screen_Trip_blank.set_pivot(0,0)
screen_Trip_blank.set_angle(0)
# create style style_screen_trip_blank_main_main_default
style_screen_trip_blank_main_main_default = lv.style_t()
style_screen_trip_blank_main_main_default.init()
style_screen_trip_blank_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_trip_blank_main_main_default.set_img_recolor_opa(0)
style_screen_trip_blank_main_main_default.set_img_opa(255)

# add style for screen_Trip_blank
screen_Trip_blank.add_style(style_screen_trip_blank_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_imgKmph = lv.img(screen)
screen_imgKmph.set_pos(195,155)
screen_imgKmph.set_size(33,19)
screen_imgKmph.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-603555955.png','rb') as f:
        screen_imgKmph_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-603555955.png')
    sys.exit()

screen_imgKmph_img = lv.img_dsc_t({
  'data_size': len(screen_imgKmph_img_data),
  'header': {'always_zero': 0, 'w': 33, 'h': 19, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_imgKmph_img_data
})

screen_imgKmph.set_src(screen_imgKmph_img)
screen_imgKmph.set_pivot(0,0)
screen_imgKmph.set_angle(0)
# create style style_screen_imgkmph_main_main_default
style_screen_imgkmph_main_main_default = lv.style_t()
style_screen_imgkmph_main_main_default.init()
style_screen_imgkmph_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_imgkmph_main_main_default.set_img_recolor_opa(0)
style_screen_imgkmph_main_main_default.set_img_opa(255)

# add style for screen_imgKmph
screen_imgKmph.add_style(style_screen_imgkmph_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_Fuelbar0 = lv.img(screen)
screen_Fuelbar0.set_pos(38,266)
screen_Fuelbar0.set_size(163,44)
screen_Fuelbar0.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1942095177.png','rb') as f:
        screen_Fuelbar0_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1942095177.png')
    sys.exit()

screen_Fuelbar0_img = lv.img_dsc_t({
  'data_size': len(screen_Fuelbar0_img_data),
  'header': {'always_zero': 0, 'w': 163, 'h': 44, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_Fuelbar0_img_data
})

screen_Fuelbar0.set_src(screen_Fuelbar0_img)
screen_Fuelbar0.set_pivot(0,0)
screen_Fuelbar0.set_angle(0)
# create style style_screen_fuelbar0_main_main_default
style_screen_fuelbar0_main_main_default = lv.style_t()
style_screen_fuelbar0_main_main_default.init()
style_screen_fuelbar0_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_fuelbar0_main_main_default.set_img_recolor_opa(0)
style_screen_fuelbar0_main_main_default.set_img_opa(255)

# add style for screen_Fuelbar0
screen_Fuelbar0.add_style(style_screen_fuelbar0_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_Fuelbar1 = lv.img(screen)
screen_Fuelbar1.set_pos(38,266)
screen_Fuelbar1.set_size(163,44)
screen_Fuelbar1.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1748989615.png','rb') as f:
        screen_Fuelbar1_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1748989615.png')
    sys.exit()

screen_Fuelbar1_img = lv.img_dsc_t({
  'data_size': len(screen_Fuelbar1_img_data),
  'header': {'always_zero': 0, 'w': 163, 'h': 44, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_Fuelbar1_img_data
})

screen_Fuelbar1.set_src(screen_Fuelbar1_img)
screen_Fuelbar1.set_pivot(0,0)
screen_Fuelbar1.set_angle(0)
# create style style_screen_fuelbar1_main_main_default
style_screen_fuelbar1_main_main_default = lv.style_t()
style_screen_fuelbar1_main_main_default.init()
style_screen_fuelbar1_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_fuelbar1_main_main_default.set_img_recolor_opa(0)
style_screen_fuelbar1_main_main_default.set_img_opa(0)

# add style for screen_Fuelbar1
screen_Fuelbar1.add_style(style_screen_fuelbar1_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_Fuelbar2 = lv.img(screen)
screen_Fuelbar2.set_pos(38,266)
screen_Fuelbar2.set_size(163,44)
screen_Fuelbar2.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp2123230384.png','rb') as f:
        screen_Fuelbar2_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp2123230384.png')
    sys.exit()

screen_Fuelbar2_img = lv.img_dsc_t({
  'data_size': len(screen_Fuelbar2_img_data),
  'header': {'always_zero': 0, 'w': 163, 'h': 44, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_Fuelbar2_img_data
})

screen_Fuelbar2.set_src(screen_Fuelbar2_img)
screen_Fuelbar2.set_pivot(0,0)
screen_Fuelbar2.set_angle(0)
# create style style_screen_fuelbar2_main_main_default
style_screen_fuelbar2_main_main_default = lv.style_t()
style_screen_fuelbar2_main_main_default.init()
style_screen_fuelbar2_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_fuelbar2_main_main_default.set_img_recolor_opa(0)
style_screen_fuelbar2_main_main_default.set_img_opa(0)

# add style for screen_Fuelbar2
screen_Fuelbar2.add_style(style_screen_fuelbar2_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_Fuelbar3 = lv.img(screen)
screen_Fuelbar3.set_pos(38,266)
screen_Fuelbar3.set_size(163,44)
screen_Fuelbar3.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-2140717105.png','rb') as f:
        screen_Fuelbar3_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-2140717105.png')
    sys.exit()

screen_Fuelbar3_img = lv.img_dsc_t({
  'data_size': len(screen_Fuelbar3_img_data),
  'header': {'always_zero': 0, 'w': 163, 'h': 44, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_Fuelbar3_img_data
})

screen_Fuelbar3.set_src(screen_Fuelbar3_img)
screen_Fuelbar3.set_pivot(0,0)
screen_Fuelbar3.set_angle(0)
# create style style_screen_fuelbar3_main_main_default
style_screen_fuelbar3_main_main_default = lv.style_t()
style_screen_fuelbar3_main_main_default.init()
style_screen_fuelbar3_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_fuelbar3_main_main_default.set_img_recolor_opa(0)
style_screen_fuelbar3_main_main_default.set_img_opa(0)

# add style for screen_Fuelbar3
screen_Fuelbar3.add_style(style_screen_fuelbar3_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_Fuelbar4 = lv.img(screen)
screen_Fuelbar4.set_pos(38,266)
screen_Fuelbar4.set_size(163,44)
screen_Fuelbar4.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-2109697298.png','rb') as f:
        screen_Fuelbar4_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-2109697298.png')
    sys.exit()

screen_Fuelbar4_img = lv.img_dsc_t({
  'data_size': len(screen_Fuelbar4_img_data),
  'header': {'always_zero': 0, 'w': 163, 'h': 44, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_Fuelbar4_img_data
})

screen_Fuelbar4.set_src(screen_Fuelbar4_img)
screen_Fuelbar4.set_pivot(0,0)
screen_Fuelbar4.set_angle(0)
# create style style_screen_fuelbar4_main_main_default
style_screen_fuelbar4_main_main_default = lv.style_t()
style_screen_fuelbar4_main_main_default.init()
style_screen_fuelbar4_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_fuelbar4_main_main_default.set_img_recolor_opa(0)
style_screen_fuelbar4_main_main_default.set_img_opa(0)

# add style for screen_Fuelbar4
screen_Fuelbar4.add_style(style_screen_fuelbar4_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_Fuelbar5 = lv.img(screen)
screen_Fuelbar5.set_pos(38,266)
screen_Fuelbar5.set_size(163,44)
screen_Fuelbar5.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-2078677491.png','rb') as f:
        screen_Fuelbar5_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-2078677491.png')
    sys.exit()

screen_Fuelbar5_img = lv.img_dsc_t({
  'data_size': len(screen_Fuelbar5_img_data),
  'header': {'always_zero': 0, 'w': 163, 'h': 44, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_Fuelbar5_img_data
})

screen_Fuelbar5.set_src(screen_Fuelbar5_img)
screen_Fuelbar5.set_pivot(0,0)
screen_Fuelbar5.set_angle(0)
# create style style_screen_fuelbar5_main_main_default
style_screen_fuelbar5_main_main_default = lv.style_t()
style_screen_fuelbar5_main_main_default.init()
style_screen_fuelbar5_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_fuelbar5_main_main_default.set_img_recolor_opa(0)
style_screen_fuelbar5_main_main_default.set_img_opa(0)

# add style for screen_Fuelbar5
screen_Fuelbar5.add_style(style_screen_fuelbar5_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_Fuelbar6 = lv.img(screen)
screen_Fuelbar6.set_pos(38,266)
screen_Fuelbar6.set_size(163,44)
screen_Fuelbar6.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-2047657684.png','rb') as f:
        screen_Fuelbar6_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-2047657684.png')
    sys.exit()

screen_Fuelbar6_img = lv.img_dsc_t({
  'data_size': len(screen_Fuelbar6_img_data),
  'header': {'always_zero': 0, 'w': 163, 'h': 44, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_Fuelbar6_img_data
})

screen_Fuelbar6.set_src(screen_Fuelbar6_img)
screen_Fuelbar6.set_pivot(0,0)
screen_Fuelbar6.set_angle(0)
# create style style_screen_fuelbar6_main_main_default
style_screen_fuelbar6_main_main_default = lv.style_t()
style_screen_fuelbar6_main_main_default.init()
style_screen_fuelbar6_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_fuelbar6_main_main_default.set_img_recolor_opa(0)
style_screen_fuelbar6_main_main_default.set_img_opa(0)

# add style for screen_Fuelbar6
screen_Fuelbar6.add_style(style_screen_fuelbar6_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_Fuelbar7 = lv.img(screen)
screen_Fuelbar7.set_pos(38,266)
screen_Fuelbar7.set_size(163,44)
screen_Fuelbar7.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-2016637877.png','rb') as f:
        screen_Fuelbar7_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-2016637877.png')
    sys.exit()

screen_Fuelbar7_img = lv.img_dsc_t({
  'data_size': len(screen_Fuelbar7_img_data),
  'header': {'always_zero': 0, 'w': 163, 'h': 44, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_Fuelbar7_img_data
})

screen_Fuelbar7.set_src(screen_Fuelbar7_img)
screen_Fuelbar7.set_pivot(0,0)
screen_Fuelbar7.set_angle(0)
# create style style_screen_fuelbar7_main_main_default
style_screen_fuelbar7_main_main_default = lv.style_t()
style_screen_fuelbar7_main_main_default.init()
style_screen_fuelbar7_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_fuelbar7_main_main_default.set_img_recolor_opa(0)
style_screen_fuelbar7_main_main_default.set_img_opa(0)

# add style for screen_Fuelbar7
screen_Fuelbar7.add_style(style_screen_fuelbar7_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_FuelWarning = lv.imgbtn(screen)
screen_FuelWarning.set_pos(110,288)
screen_FuelWarning.set_size(20,19)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp2578266.png','rb') as f:
        screen_FuelWarning_imgReleased_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp2578266.png')
    sys.exit()

screen_FuelWarning_imgReleased = lv.img_dsc_t({
  'data_size': len(screen_FuelWarning_imgReleased_data),
  'header': {'always_zero': 0, 'w': 20, 'h': 19, 'cf': lv.img.CF.TRUE_COLOR},
  'data': screen_FuelWarning_imgReleased_data
})
screen_FuelWarning.set_src(lv.imgbtn.STATE.RELEASED, screen_FuelWarning_imgReleased, None, None)

try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1093437134.png','rb') as f:
        screen_FuelWarning_imgPressed_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1093437134.png')
    sys.exit()

screen_FuelWarning_imgPressed = lv.img_dsc_t({
  'data_size': len(screen_FuelWarning_imgPressed_data),
  'header': {'always_zero': 0, 'w': 20, 'h': 19, 'cf': lv.img.CF.TRUE_COLOR},
  'data': screen_FuelWarning_imgPressed_data
})
screen_FuelWarning.set_src(lv.imgbtn.STATE.PRESSED, screen_FuelWarning_imgPressed, None, None)




screen_FuelWarning.add_flag(lv.obj.FLAG.CHECKABLE)
# create style style_screen_fuelwarning_main_main_default
style_screen_fuelwarning_main_main_default = lv.style_t()
style_screen_fuelwarning_main_main_default.init()
style_screen_fuelwarning_main_main_default.set_text_color(lv.color_make(0x00,0x00,0x00))
try:
    style_screen_fuelwarning_main_main_default.set_text_font(lv.font_simsun_12)
except AttributeError:
    try:
        style_screen_fuelwarning_main_main_default.set_text_font(lv.font_montserrat_12)
    except AttributeError:
        style_screen_fuelwarning_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_fuelwarning_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_fuelwarning_main_main_default.set_img_recolor_opa(0)
style_screen_fuelwarning_main_main_default.set_img_opa(255)

# add style for screen_FuelWarning
screen_FuelWarning.add_style(style_screen_fuelwarning_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_screen_fuelwarning_main_main_pressed
style_screen_fuelwarning_main_main_pressed = lv.style_t()
style_screen_fuelwarning_main_main_pressed.init()
style_screen_fuelwarning_main_main_pressed.set_text_color(lv.color_make(0xFF,0x33,0xFF))
try:
    style_screen_fuelwarning_main_main_pressed.set_text_font(lv.font_simsun_16)
except AttributeError:
    try:
        style_screen_fuelwarning_main_main_pressed.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_screen_fuelwarning_main_main_pressed.set_text_font(lv.font_montserrat_16)
style_screen_fuelwarning_main_main_pressed.set_img_recolor(lv.color_make(0x00,0x00,0x00))
style_screen_fuelwarning_main_main_pressed.set_img_recolor_opa(0)

# add style for screen_FuelWarning
screen_FuelWarning.add_style(style_screen_fuelwarning_main_main_pressed, lv.PART.MAIN|lv.STATE.PRESSED)

# create style style_screen_fuelwarning_main_main_checked
style_screen_fuelwarning_main_main_checked = lv.style_t()
style_screen_fuelwarning_main_main_checked.init()
style_screen_fuelwarning_main_main_checked.set_text_color(lv.color_make(0xFF,0x33,0xFF))
try:
    style_screen_fuelwarning_main_main_checked.set_text_font(lv.font_simsun_16)
except AttributeError:
    try:
        style_screen_fuelwarning_main_main_checked.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_screen_fuelwarning_main_main_checked.set_text_font(lv.font_montserrat_16)
style_screen_fuelwarning_main_main_checked.set_img_recolor(lv.color_make(0x00,0x00,0x00))
style_screen_fuelwarning_main_main_checked.set_img_recolor_opa(0)

# add style for screen_FuelWarning
screen_FuelWarning.add_style(style_screen_fuelwarning_main_main_checked, lv.PART.MAIN|lv.STATE.CHECKED)

screen_Gear_Symbol = lv.img(screen)
screen_Gear_Symbol.set_pos(17,148)
screen_Gear_Symbol.set_size(10,24)
screen_Gear_Symbol.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-378950901.png','rb') as f:
        screen_Gear_Symbol_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-378950901.png')
    sys.exit()

screen_Gear_Symbol_img = lv.img_dsc_t({
  'data_size': len(screen_Gear_Symbol_img_data),
  'header': {'always_zero': 0, 'w': 10, 'h': 24, 'cf': lv.img.CF.TRUE_COLOR},
  'data': screen_Gear_Symbol_img_data
})

screen_Gear_Symbol.set_src(screen_Gear_Symbol_img)
screen_Gear_Symbol.set_pivot(0,0)
screen_Gear_Symbol.set_angle(0)
# create style style_screen_gear_symbol_main_main_default
style_screen_gear_symbol_main_main_default = lv.style_t()
style_screen_gear_symbol_main_main_default.init()
style_screen_gear_symbol_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_gear_symbol_main_main_default.set_img_recolor_opa(0)
style_screen_gear_symbol_main_main_default.set_img_opa(255)

# add style for screen_Gear_Symbol
screen_Gear_Symbol.add_style(style_screen_gear_symbol_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_Gear_Position_Number = lv.label(screen)
screen_Gear_Position_Number.set_pos(31,148)
screen_Gear_Position_Number.set_size(14,26)
screen_Gear_Position_Number.set_text("2")
screen_Gear_Position_Number.set_long_mode(lv.label.LONG.WRAP)
screen_Gear_Position_Number.set_style_text_align(lv.TEXT_ALIGN.CENTER, 0)
# create style style_screen_gear_position_number_main_main_default
style_screen_gear_position_number_main_main_default = lv.style_t()
style_screen_gear_position_number_main_main_default.init()
style_screen_gear_position_number_main_main_default.set_radius(0)
style_screen_gear_position_number_main_main_default.set_bg_color(lv.color_make(0x00,0x00,0x00))
style_screen_gear_position_number_main_main_default.set_bg_grad_color(lv.color_make(0x00,0x00,0x00))
style_screen_gear_position_number_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_screen_gear_position_number_main_main_default.set_bg_opa(0)
style_screen_gear_position_number_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_screen_gear_position_number_main_main_default.set_text_font(lv.font_FjallaOne_Regular_30)
except AttributeError:
    try:
        style_screen_gear_position_number_main_main_default.set_text_font(lv.font_montserrat_30)
    except AttributeError:
        style_screen_gear_position_number_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_gear_position_number_main_main_default.set_text_letter_space(0)
style_screen_gear_position_number_main_main_default.set_pad_left(0)
style_screen_gear_position_number_main_main_default.set_pad_right(0)
style_screen_gear_position_number_main_main_default.set_pad_top(0)
style_screen_gear_position_number_main_main_default.set_pad_bottom(0)

# add style for screen_Gear_Position_Number
screen_Gear_Position_Number.add_style(style_screen_gear_position_number_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_Clock_hour = lv.label(screen)
screen_Clock_hour.set_pos(97,81)
screen_Clock_hour.set_size(13,12)
screen_Clock_hour.set_text("24")
screen_Clock_hour.set_long_mode(lv.label.LONG.WRAP)
screen_Clock_hour.set_style_text_align(lv.TEXT_ALIGN.RIGHT, 0)
# create style style_screen_clock_hour_main_main_default
style_screen_clock_hour_main_main_default = lv.style_t()
style_screen_clock_hour_main_main_default.init()
style_screen_clock_hour_main_main_default.set_radius(0)
style_screen_clock_hour_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_screen_clock_hour_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_clock_hour_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_screen_clock_hour_main_main_default.set_bg_opa(0)
style_screen_clock_hour_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_screen_clock_hour_main_main_default.set_text_font(lv.font_FjallaOne_Regular_19)
except AttributeError:
    try:
        style_screen_clock_hour_main_main_default.set_text_font(lv.font_montserrat_19)
    except AttributeError:
        style_screen_clock_hour_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_clock_hour_main_main_default.set_text_letter_space(2)
style_screen_clock_hour_main_main_default.set_pad_left(0)
style_screen_clock_hour_main_main_default.set_pad_right(0)
style_screen_clock_hour_main_main_default.set_pad_top(0)
style_screen_clock_hour_main_main_default.set_pad_bottom(0)

# add style for screen_Clock_hour
screen_Clock_hour.add_style(style_screen_clock_hour_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_Clock_min = lv.label(screen)
screen_Clock_min.set_pos(111,81)
screen_Clock_min.set_size(15,12)
screen_Clock_min.set_text("60")
screen_Clock_min.set_long_mode(lv.label.LONG.WRAP)
screen_Clock_min.set_style_text_align(lv.TEXT_ALIGN.LEFT, 0)
# create style style_screen_clock_min_main_main_default
style_screen_clock_min_main_main_default = lv.style_t()
style_screen_clock_min_main_main_default.init()
style_screen_clock_min_main_main_default.set_radius(0)
style_screen_clock_min_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_screen_clock_min_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_clock_min_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_screen_clock_min_main_main_default.set_bg_opa(0)
style_screen_clock_min_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_screen_clock_min_main_main_default.set_text_font(lv.font_FjallaOne_Regular_19)
except AttributeError:
    try:
        style_screen_clock_min_main_main_default.set_text_font(lv.font_montserrat_19)
    except AttributeError:
        style_screen_clock_min_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_clock_min_main_main_default.set_text_letter_space(2)
style_screen_clock_min_main_main_default.set_pad_left(0)
style_screen_clock_min_main_main_default.set_pad_right(0)
style_screen_clock_min_main_main_default.set_pad_top(0)
style_screen_clock_min_main_main_default.set_pad_bottom(0)

# add style for screen_Clock_min
screen_Clock_min.add_style(style_screen_clock_min_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_Clock_Colan = lv.label(screen)
screen_Clock_Colan.set_pos(107,87)
screen_Clock_Colan.set_size(3,10)
screen_Clock_Colan.set_text(":")
screen_Clock_Colan.set_long_mode(lv.label.LONG.WRAP)
screen_Clock_Colan.set_style_text_align(lv.TEXT_ALIGN.CENTER, 0)
# create style style_screen_clock_colan_main_main_default
style_screen_clock_colan_main_main_default = lv.style_t()
style_screen_clock_colan_main_main_default.init()
style_screen_clock_colan_main_main_default.set_radius(0)
style_screen_clock_colan_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_screen_clock_colan_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_clock_colan_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_screen_clock_colan_main_main_default.set_bg_opa(0)
style_screen_clock_colan_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_screen_clock_colan_main_main_default.set_text_font(lv.font_FjallaOne_Regular_19)
except AttributeError:
    try:
        style_screen_clock_colan_main_main_default.set_text_font(lv.font_montserrat_19)
    except AttributeError:
        style_screen_clock_colan_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_clock_colan_main_main_default.set_text_letter_space(2)
style_screen_clock_colan_main_main_default.set_pad_left(0)
style_screen_clock_colan_main_main_default.set_pad_right(0)
style_screen_clock_colan_main_main_default.set_pad_top(0)
style_screen_clock_colan_main_main_default.set_pad_bottom(0)

# add style for screen_Clock_Colan
screen_Clock_Colan.add_style(style_screen_clock_colan_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBarBlank = lv.img(screen)
screen_TachoBarBlank.set_pos(3,8)
screen_TachoBarBlank.set_size(231,78)
screen_TachoBarBlank.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp1610730252.png','rb') as f:
        screen_TachoBarBlank_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp1610730252.png')
    sys.exit()

screen_TachoBarBlank_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBarBlank_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBarBlank_img_data
})

screen_TachoBarBlank.set_src(screen_TachoBarBlank_img)
screen_TachoBarBlank.set_pivot(0,0)
screen_TachoBarBlank.set_angle(0)
# create style style_screen_tachobarblank_main_main_default
style_screen_tachobarblank_main_main_default = lv.style_t()
style_screen_tachobarblank_main_main_default.init()
style_screen_tachobarblank_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobarblank_main_main_default.set_img_recolor_opa(0)
style_screen_tachobarblank_main_main_default.set_img_opa(0)

# add style for screen_TachoBarBlank
screen_TachoBarBlank.add_style(style_screen_tachobarblank_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TripB = lv.img(screen)
screen_TripB.set_pos(105,252)
screen_TripB.set_size(30,30)
screen_TripB.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp752868251.png','rb') as f:
        screen_TripB_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp752868251.png')
    sys.exit()

screen_TripB_img = lv.img_dsc_t({
  'data_size': len(screen_TripB_img_data),
  'header': {'always_zero': 0, 'w': 30, 'h': 30, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TripB_img_data
})

screen_TripB.set_src(screen_TripB_img)
screen_TripB.set_pivot(0,0)
screen_TripB.set_angle(0)
# create style style_screen_tripb_main_main_default
style_screen_tripb_main_main_default = lv.style_t()
style_screen_tripb_main_main_default.init()
style_screen_tripb_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tripb_main_main_default.set_img_recolor_opa(0)
style_screen_tripb_main_main_default.set_img_opa(0)

# add style for screen_TripB
screen_TripB.add_style(style_screen_tripb_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_Service_Icon = lv.img(screen)
screen_Service_Icon.set_pos(98,252)
screen_Service_Icon.set_size(30,30)
screen_Service_Icon.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-308500653.png','rb') as f:
        screen_Service_Icon_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-308500653.png')
    sys.exit()

screen_Service_Icon_img = lv.img_dsc_t({
  'data_size': len(screen_Service_Icon_img_data),
  'header': {'always_zero': 0, 'w': 30, 'h': 30, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_Service_Icon_img_data
})

screen_Service_Icon.set_src(screen_Service_Icon_img)
screen_Service_Icon.set_pivot(0,0)
screen_Service_Icon.set_angle(0)
# create style style_screen_service_icon_main_main_default
style_screen_service_icon_main_main_default = lv.style_t()
style_screen_service_icon_main_main_default.init()
style_screen_service_icon_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_service_icon_main_main_default.set_img_recolor_opa(0)
style_screen_service_icon_main_main_default.set_img_opa(0)

# add style for screen_Service_Icon
screen_Service_Icon.add_style(style_screen_service_icon_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_Gear_UP_Advisory = lv.imgbtn(screen)
screen_Gear_UP_Advisory.set_pos(31,135)
screen_Gear_UP_Advisory.set_size(13,9)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp891757064.png','rb') as f:
        screen_Gear_UP_Advisory_imgReleased_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp891757064.png')
    sys.exit()

screen_Gear_UP_Advisory_imgReleased = lv.img_dsc_t({
  'data_size': len(screen_Gear_UP_Advisory_imgReleased_data),
  'header': {'always_zero': 0, 'w': 13, 'h': 9, 'cf': lv.img.CF.TRUE_COLOR},
  'data': screen_Gear_UP_Advisory_imgReleased_data
})
screen_Gear_UP_Advisory.set_src(lv.imgbtn.STATE.RELEASED, screen_Gear_UP_Advisory_imgReleased, None, None)

try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1001527792.png','rb') as f:
        screen_Gear_UP_Advisory_imgPressed_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1001527792.png')
    sys.exit()

screen_Gear_UP_Advisory_imgPressed = lv.img_dsc_t({
  'data_size': len(screen_Gear_UP_Advisory_imgPressed_data),
  'header': {'always_zero': 0, 'w': 13, 'h': 9, 'cf': lv.img.CF.TRUE_COLOR},
  'data': screen_Gear_UP_Advisory_imgPressed_data
})
screen_Gear_UP_Advisory.set_src(lv.imgbtn.STATE.PRESSED, screen_Gear_UP_Advisory_imgPressed, None, None)




screen_Gear_UP_Advisory.add_flag(lv.obj.FLAG.CHECKABLE)
# create style style_screen_gear_up_advisory_main_main_default
style_screen_gear_up_advisory_main_main_default = lv.style_t()
style_screen_gear_up_advisory_main_main_default.init()
style_screen_gear_up_advisory_main_main_default.set_text_color(lv.color_make(0x00,0x00,0x00))
try:
    style_screen_gear_up_advisory_main_main_default.set_text_font(lv.font_simsun_12)
except AttributeError:
    try:
        style_screen_gear_up_advisory_main_main_default.set_text_font(lv.font_montserrat_12)
    except AttributeError:
        style_screen_gear_up_advisory_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_gear_up_advisory_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_gear_up_advisory_main_main_default.set_img_recolor_opa(0)
style_screen_gear_up_advisory_main_main_default.set_img_opa(254)

# add style for screen_Gear_UP_Advisory
screen_Gear_UP_Advisory.add_style(style_screen_gear_up_advisory_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_screen_gear_up_advisory_main_main_pressed
style_screen_gear_up_advisory_main_main_pressed = lv.style_t()
style_screen_gear_up_advisory_main_main_pressed.init()
style_screen_gear_up_advisory_main_main_pressed.set_text_color(lv.color_make(0xFF,0x33,0xFF))
try:
    style_screen_gear_up_advisory_main_main_pressed.set_text_font(lv.font_simsun_16)
except AttributeError:
    try:
        style_screen_gear_up_advisory_main_main_pressed.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_screen_gear_up_advisory_main_main_pressed.set_text_font(lv.font_montserrat_16)
style_screen_gear_up_advisory_main_main_pressed.set_img_recolor(lv.color_make(0x00,0x00,0x00))
style_screen_gear_up_advisory_main_main_pressed.set_img_recolor_opa(0)

# add style for screen_Gear_UP_Advisory
screen_Gear_UP_Advisory.add_style(style_screen_gear_up_advisory_main_main_pressed, lv.PART.MAIN|lv.STATE.PRESSED)

# create style style_screen_gear_up_advisory_main_main_checked
style_screen_gear_up_advisory_main_main_checked = lv.style_t()
style_screen_gear_up_advisory_main_main_checked.init()
style_screen_gear_up_advisory_main_main_checked.set_text_color(lv.color_make(0xFF,0x33,0xFF))
try:
    style_screen_gear_up_advisory_main_main_checked.set_text_font(lv.font_simsun_16)
except AttributeError:
    try:
        style_screen_gear_up_advisory_main_main_checked.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_screen_gear_up_advisory_main_main_checked.set_text_font(lv.font_montserrat_16)
style_screen_gear_up_advisory_main_main_checked.set_img_recolor(lv.color_make(0x00,0x00,0x00))
style_screen_gear_up_advisory_main_main_checked.set_img_recolor_opa(0)

# add style for screen_Gear_UP_Advisory
screen_Gear_UP_Advisory.add_style(style_screen_gear_up_advisory_main_main_checked, lv.PART.MAIN|lv.STATE.CHECKED)

screen_Gear_Down_Advisory = lv.imgbtn(screen)
screen_Gear_Down_Advisory.set_pos(31,178)
screen_Gear_Down_Advisory.set_size(13,9)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1368468977.png','rb') as f:
        screen_Gear_Down_Advisory_imgReleased_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1368468977.png')
    sys.exit()

screen_Gear_Down_Advisory_imgReleased = lv.img_dsc_t({
  'data_size': len(screen_Gear_Down_Advisory_imgReleased_data),
  'header': {'always_zero': 0, 'w': 13, 'h': 9, 'cf': lv.img.CF.TRUE_COLOR},
  'data': screen_Gear_Down_Advisory_imgReleased_data
})
screen_Gear_Down_Advisory.set_src(lv.imgbtn.STATE.RELEASED, screen_Gear_Down_Advisory_imgReleased, None, None)

try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp1945908969.png','rb') as f:
        screen_Gear_Down_Advisory_imgPressed_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp1945908969.png')
    sys.exit()

screen_Gear_Down_Advisory_imgPressed = lv.img_dsc_t({
  'data_size': len(screen_Gear_Down_Advisory_imgPressed_data),
  'header': {'always_zero': 0, 'w': 13, 'h': 9, 'cf': lv.img.CF.TRUE_COLOR},
  'data': screen_Gear_Down_Advisory_imgPressed_data
})
screen_Gear_Down_Advisory.set_src(lv.imgbtn.STATE.PRESSED, screen_Gear_Down_Advisory_imgPressed, None, None)




screen_Gear_Down_Advisory.add_flag(lv.obj.FLAG.CHECKABLE)
# create style style_screen_gear_down_advisory_main_main_default
style_screen_gear_down_advisory_main_main_default = lv.style_t()
style_screen_gear_down_advisory_main_main_default.init()
style_screen_gear_down_advisory_main_main_default.set_text_color(lv.color_make(0x00,0x00,0x00))
try:
    style_screen_gear_down_advisory_main_main_default.set_text_font(lv.font_simsun_12)
except AttributeError:
    try:
        style_screen_gear_down_advisory_main_main_default.set_text_font(lv.font_montserrat_12)
    except AttributeError:
        style_screen_gear_down_advisory_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_gear_down_advisory_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_gear_down_advisory_main_main_default.set_img_recolor_opa(0)
style_screen_gear_down_advisory_main_main_default.set_img_opa(253)

# add style for screen_Gear_Down_Advisory
screen_Gear_Down_Advisory.add_style(style_screen_gear_down_advisory_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_screen_gear_down_advisory_main_main_pressed
style_screen_gear_down_advisory_main_main_pressed = lv.style_t()
style_screen_gear_down_advisory_main_main_pressed.init()
style_screen_gear_down_advisory_main_main_pressed.set_text_color(lv.color_make(0xFF,0x33,0xFF))
try:
    style_screen_gear_down_advisory_main_main_pressed.set_text_font(lv.font_simsun_16)
except AttributeError:
    try:
        style_screen_gear_down_advisory_main_main_pressed.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_screen_gear_down_advisory_main_main_pressed.set_text_font(lv.font_montserrat_16)
style_screen_gear_down_advisory_main_main_pressed.set_img_recolor(lv.color_make(0x00,0x00,0x00))
style_screen_gear_down_advisory_main_main_pressed.set_img_recolor_opa(0)

# add style for screen_Gear_Down_Advisory
screen_Gear_Down_Advisory.add_style(style_screen_gear_down_advisory_main_main_pressed, lv.PART.MAIN|lv.STATE.PRESSED)

# create style style_screen_gear_down_advisory_main_main_checked
style_screen_gear_down_advisory_main_main_checked = lv.style_t()
style_screen_gear_down_advisory_main_main_checked.init()
style_screen_gear_down_advisory_main_main_checked.set_text_color(lv.color_make(0xFF,0x33,0xFF))
try:
    style_screen_gear_down_advisory_main_main_checked.set_text_font(lv.font_simsun_16)
except AttributeError:
    try:
        style_screen_gear_down_advisory_main_main_checked.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_screen_gear_down_advisory_main_main_checked.set_text_font(lv.font_montserrat_16)
style_screen_gear_down_advisory_main_main_checked.set_img_recolor(lv.color_make(0x00,0x00,0x00))
style_screen_gear_down_advisory_main_main_checked.set_img_recolor_opa(0)

# add style for screen_Gear_Down_Advisory
screen_Gear_Down_Advisory.add_style(style_screen_gear_down_advisory_main_main_checked, lv.PART.MAIN|lv.STATE.CHECKED)

screen_Service_Due = lv.imgbtn(screen)
screen_Service_Due.set_pos(214,224)
screen_Service_Due.set_size(22,25)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1490251127.png','rb') as f:
        screen_Service_Due_imgReleased_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1490251127.png')
    sys.exit()

screen_Service_Due_imgReleased = lv.img_dsc_t({
  'data_size': len(screen_Service_Due_imgReleased_data),
  'header': {'always_zero': 0, 'w': 22, 'h': 25, 'cf': lv.img.CF.TRUE_COLOR},
  'data': screen_Service_Due_imgReleased_data
})
screen_Service_Due.set_src(lv.imgbtn.STATE.RELEASED, screen_Service_Due_imgReleased, None, None)

try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1130780031.png','rb') as f:
        screen_Service_Due_imgPressed_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1130780031.png')
    sys.exit()

screen_Service_Due_imgPressed = lv.img_dsc_t({
  'data_size': len(screen_Service_Due_imgPressed_data),
  'header': {'always_zero': 0, 'w': 22, 'h': 25, 'cf': lv.img.CF.TRUE_COLOR},
  'data': screen_Service_Due_imgPressed_data
})
screen_Service_Due.set_src(lv.imgbtn.STATE.PRESSED, screen_Service_Due_imgPressed, None, None)




screen_Service_Due.add_flag(lv.obj.FLAG.CHECKABLE)
# create style style_screen_service_due_main_main_default
style_screen_service_due_main_main_default = lv.style_t()
style_screen_service_due_main_main_default.init()
style_screen_service_due_main_main_default.set_text_color(lv.color_make(0x00,0x00,0x00))
try:
    style_screen_service_due_main_main_default.set_text_font(lv.font_simsun_12)
except AttributeError:
    try:
        style_screen_service_due_main_main_default.set_text_font(lv.font_montserrat_12)
    except AttributeError:
        style_screen_service_due_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_service_due_main_main_default.set_img_recolor(lv.color_make(0x00,0x00,0x00))
style_screen_service_due_main_main_default.set_img_recolor_opa(3)
style_screen_service_due_main_main_default.set_img_opa(255)

# add style for screen_Service_Due
screen_Service_Due.add_style(style_screen_service_due_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_screen_service_due_main_main_pressed
style_screen_service_due_main_main_pressed = lv.style_t()
style_screen_service_due_main_main_pressed.init()
style_screen_service_due_main_main_pressed.set_text_color(lv.color_make(0xFF,0x33,0xFF))
try:
    style_screen_service_due_main_main_pressed.set_text_font(lv.font_simsun_16)
except AttributeError:
    try:
        style_screen_service_due_main_main_pressed.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_screen_service_due_main_main_pressed.set_text_font(lv.font_montserrat_16)
style_screen_service_due_main_main_pressed.set_img_recolor(lv.color_make(0x00,0x00,0x00))
style_screen_service_due_main_main_pressed.set_img_recolor_opa(0)

# add style for screen_Service_Due
screen_Service_Due.add_style(style_screen_service_due_main_main_pressed, lv.PART.MAIN|lv.STATE.PRESSED)

# create style style_screen_service_due_main_main_checked
style_screen_service_due_main_main_checked = lv.style_t()
style_screen_service_due_main_main_checked.init()
style_screen_service_due_main_main_checked.set_text_color(lv.color_make(0xFF,0x33,0xFF))
try:
    style_screen_service_due_main_main_checked.set_text_font(lv.font_simsun_16)
except AttributeError:
    try:
        style_screen_service_due_main_main_checked.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_screen_service_due_main_main_checked.set_text_font(lv.font_montserrat_16)
style_screen_service_due_main_main_checked.set_img_recolor(lv.color_make(0x00,0x00,0x00))
style_screen_service_due_main_main_checked.set_img_recolor_opa(0)

# add style for screen_Service_Due
screen_Service_Due.add_style(style_screen_service_due_main_main_checked, lv.PART.MAIN|lv.STATE.CHECKED)

screen_Black = lv.img(screen)
screen_Black.set_pos(48,99)
screen_Black.set_size(9,9)
screen_Black.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1087722961.png','rb') as f:
        screen_Black_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1087722961.png')
    sys.exit()

screen_Black_img = lv.img_dsc_t({
  'data_size': len(screen_Black_img_data),
  'header': {'always_zero': 0, 'w': 9, 'h': 9, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_Black_img_data
})

screen_Black.set_src(screen_Black_img)
screen_Black.set_pivot(0,0)
screen_Black.set_angle(0)
# create style style_screen_black_main_main_default
style_screen_black_main_main_default = lv.style_t()
style_screen_black_main_main_default.init()
style_screen_black_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_black_main_main_default.set_img_recolor_opa(0)
style_screen_black_main_main_default.set_img_opa(255)

# add style for screen_Black
screen_Black.add_style(style_screen_black_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar0 = lv.img(screen)
screen_TachoBar0.set_pos(3,8)
screen_TachoBar0.set_size(231,78)
screen_TachoBar0.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-492510385.png','rb') as f:
        screen_TachoBar0_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-492510385.png')
    sys.exit()

screen_TachoBar0_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar0_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar0_img_data
})

screen_TachoBar0.set_src(screen_TachoBar0_img)
screen_TachoBar0.set_pivot(0,0)
screen_TachoBar0.set_angle(0)
# create style style_screen_tachobar0_main_main_default
style_screen_tachobar0_main_main_default = lv.style_t()
style_screen_tachobar0_main_main_default.init()
style_screen_tachobar0_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar0_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar0_main_main_default.set_img_opa(255)

# add style for screen_TachoBar0
screen_TachoBar0.add_style(style_screen_tachobar0_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar0_1 = lv.img(screen)
screen_TachoBar0_1.set_pos(3,8)
screen_TachoBar0_1.set_size(231,78)
screen_TachoBar0_1.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-461490578.png','rb') as f:
        screen_TachoBar0_1_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-461490578.png')
    sys.exit()

screen_TachoBar0_1_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar0_1_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar0_1_img_data
})

screen_TachoBar0_1.set_src(screen_TachoBar0_1_img)
screen_TachoBar0_1.set_pivot(0,0)
screen_TachoBar0_1.set_angle(0)
# create style style_screen_tachobar0_1_main_main_default
style_screen_tachobar0_1_main_main_default = lv.style_t()
style_screen_tachobar0_1_main_main_default.init()
style_screen_tachobar0_1_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar0_1_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar0_1_main_main_default.set_img_opa(0)

# add style for screen_TachoBar0_1
screen_TachoBar0_1.add_style(style_screen_tachobar0_1_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar0_2 = lv.img(screen)
screen_TachoBar0_2.set_pos(3,8)
screen_TachoBar0_2.set_size(231,78)
screen_TachoBar0_2.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-430470771.png','rb') as f:
        screen_TachoBar0_2_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-430470771.png')
    sys.exit()

screen_TachoBar0_2_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar0_2_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar0_2_img_data
})

screen_TachoBar0_2.set_src(screen_TachoBar0_2_img)
screen_TachoBar0_2.set_pivot(0,0)
screen_TachoBar0_2.set_angle(0)
# create style style_screen_tachobar0_2_main_main_default
style_screen_tachobar0_2_main_main_default = lv.style_t()
style_screen_tachobar0_2_main_main_default.init()
style_screen_tachobar0_2_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar0_2_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar0_2_main_main_default.set_img_opa(0)

# add style for screen_TachoBar0_2
screen_TachoBar0_2.add_style(style_screen_tachobar0_2_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar0_3 = lv.img(screen)
screen_TachoBar0_3.set_pos(3,8)
screen_TachoBar0_3.set_size(231,78)
screen_TachoBar0_3.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-399450964.png','rb') as f:
        screen_TachoBar0_3_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-399450964.png')
    sys.exit()

screen_TachoBar0_3_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar0_3_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar0_3_img_data
})

screen_TachoBar0_3.set_src(screen_TachoBar0_3_img)
screen_TachoBar0_3.set_pivot(0,0)
screen_TachoBar0_3.set_angle(0)
# create style style_screen_tachobar0_3_main_main_default
style_screen_tachobar0_3_main_main_default = lv.style_t()
style_screen_tachobar0_3_main_main_default.init()
style_screen_tachobar0_3_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar0_3_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar0_3_main_main_default.set_img_opa(0)

# add style for screen_TachoBar0_3
screen_TachoBar0_3.add_style(style_screen_tachobar0_3_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar1 = lv.img(screen)
screen_TachoBar1.set_pos(3,8)
screen_TachoBar1.set_size(231,78)
screen_TachoBar1.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-368431157.png','rb') as f:
        screen_TachoBar1_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-368431157.png')
    sys.exit()

screen_TachoBar1_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar1_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar1_img_data
})

screen_TachoBar1.set_src(screen_TachoBar1_img)
screen_TachoBar1.set_pivot(0,0)
screen_TachoBar1.set_angle(0)
# create style style_screen_tachobar1_main_main_default
style_screen_tachobar1_main_main_default = lv.style_t()
style_screen_tachobar1_main_main_default.init()
style_screen_tachobar1_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar1_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar1_main_main_default.set_img_opa(0)

# add style for screen_TachoBar1
screen_TachoBar1.add_style(style_screen_tachobar1_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar1_0 = lv.img(screen)
screen_TachoBar1_0.set_pos(3,8)
screen_TachoBar1_0.set_size(231,78)
screen_TachoBar1_0.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-337411350.png','rb') as f:
        screen_TachoBar1_0_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-337411350.png')
    sys.exit()

screen_TachoBar1_0_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar1_0_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar1_0_img_data
})

screen_TachoBar1_0.set_src(screen_TachoBar1_0_img)
screen_TachoBar1_0.set_pivot(0,0)
screen_TachoBar1_0.set_angle(0)
# create style style_screen_tachobar1_0_main_main_default
style_screen_tachobar1_0_main_main_default = lv.style_t()
style_screen_tachobar1_0_main_main_default.init()
style_screen_tachobar1_0_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar1_0_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar1_0_main_main_default.set_img_opa(0)

# add style for screen_TachoBar1_0
screen_TachoBar1_0.add_style(style_screen_tachobar1_0_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar1_1 = lv.img(screen)
screen_TachoBar1_1.set_pos(3,8)
screen_TachoBar1_1.set_size(231,78)
screen_TachoBar1_1.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-306391543.png','rb') as f:
        screen_TachoBar1_1_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-306391543.png')
    sys.exit()

screen_TachoBar1_1_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar1_1_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar1_1_img_data
})

screen_TachoBar1_1.set_src(screen_TachoBar1_1_img)
screen_TachoBar1_1.set_pivot(0,0)
screen_TachoBar1_1.set_angle(0)
# create style style_screen_tachobar1_1_main_main_default
style_screen_tachobar1_1_main_main_default = lv.style_t()
style_screen_tachobar1_1_main_main_default.init()
style_screen_tachobar1_1_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar1_1_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar1_1_main_main_default.set_img_opa(0)

# add style for screen_TachoBar1_1
screen_TachoBar1_1.add_style(style_screen_tachobar1_1_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar1_2 = lv.img(screen)
screen_TachoBar1_2.set_pos(3,8)
screen_TachoBar1_2.set_size(231,78)
screen_TachoBar1_2.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-275371736.png','rb') as f:
        screen_TachoBar1_2_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-275371736.png')
    sys.exit()

screen_TachoBar1_2_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar1_2_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar1_2_img_data
})

screen_TachoBar1_2.set_src(screen_TachoBar1_2_img)
screen_TachoBar1_2.set_pivot(0,0)
screen_TachoBar1_2.set_angle(0)
# create style style_screen_tachobar1_2_main_main_default
style_screen_tachobar1_2_main_main_default = lv.style_t()
style_screen_tachobar1_2_main_main_default.init()
style_screen_tachobar1_2_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar1_2_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar1_2_main_main_default.set_img_opa(0)

# add style for screen_TachoBar1_2
screen_TachoBar1_2.add_style(style_screen_tachobar1_2_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar2 = lv.img(screen)
screen_TachoBar2.set_pos(3,8)
screen_TachoBar2.set_size(231,78)
screen_TachoBar2.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-244351929.png','rb') as f:
        screen_TachoBar2_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-244351929.png')
    sys.exit()

screen_TachoBar2_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar2_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar2_img_data
})

screen_TachoBar2.set_src(screen_TachoBar2_img)
screen_TachoBar2.set_pivot(0,0)
screen_TachoBar2.set_angle(0)
# create style style_screen_tachobar2_main_main_default
style_screen_tachobar2_main_main_default = lv.style_t()
style_screen_tachobar2_main_main_default.init()
style_screen_tachobar2_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar2_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar2_main_main_default.set_img_opa(0)

# add style for screen_TachoBar2
screen_TachoBar2.add_style(style_screen_tachobar2_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar2_0 = lv.img(screen)
screen_TachoBar2_0.set_pos(3,8)
screen_TachoBar2_0.set_size(231,78)
screen_TachoBar2_0.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-213332122.png','rb') as f:
        screen_TachoBar2_0_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-213332122.png')
    sys.exit()

screen_TachoBar2_0_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar2_0_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar2_0_img_data
})

screen_TachoBar2_0.set_src(screen_TachoBar2_0_img)
screen_TachoBar2_0.set_pivot(0,0)
screen_TachoBar2_0.set_angle(0)
# create style style_screen_tachobar2_0_main_main_default
style_screen_tachobar2_0_main_main_default = lv.style_t()
style_screen_tachobar2_0_main_main_default.init()
style_screen_tachobar2_0_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar2_0_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar2_0_main_main_default.set_img_opa(0)

# add style for screen_TachoBar2_0
screen_TachoBar2_0.add_style(style_screen_tachobar2_0_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar2_1 = lv.img(screen)
screen_TachoBar2_1.set_pos(3,8)
screen_TachoBar2_1.set_size(231,78)
screen_TachoBar2_1.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp469103632.png','rb') as f:
        screen_TachoBar2_1_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp469103632.png')
    sys.exit()

screen_TachoBar2_1_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar2_1_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar2_1_img_data
})

screen_TachoBar2_1.set_src(screen_TachoBar2_1_img)
screen_TachoBar2_1.set_pivot(0,0)
screen_TachoBar2_1.set_angle(0)
# create style style_screen_tachobar2_1_main_main_default
style_screen_tachobar2_1_main_main_default = lv.style_t()
style_screen_tachobar2_1_main_main_default.init()
style_screen_tachobar2_1_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar2_1_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar2_1_main_main_default.set_img_opa(0)

# add style for screen_TachoBar2_1
screen_TachoBar2_1.add_style(style_screen_tachobar2_1_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar2_2 = lv.img(screen)
screen_TachoBar2_2.set_pos(3,8)
screen_TachoBar2_2.set_size(231,78)
screen_TachoBar2_2.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp500123439.png','rb') as f:
        screen_TachoBar2_2_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp500123439.png')
    sys.exit()

screen_TachoBar2_2_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar2_2_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar2_2_img_data
})

screen_TachoBar2_2.set_src(screen_TachoBar2_2_img)
screen_TachoBar2_2.set_pivot(0,0)
screen_TachoBar2_2.set_angle(0)
# create style style_screen_tachobar2_2_main_main_default
style_screen_tachobar2_2_main_main_default = lv.style_t()
style_screen_tachobar2_2_main_main_default.init()
style_screen_tachobar2_2_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar2_2_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar2_2_main_main_default.set_img_opa(0)

# add style for screen_TachoBar2_2
screen_TachoBar2_2.add_style(style_screen_tachobar2_2_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar3 = lv.img(screen)
screen_TachoBar3.set_pos(3,8)
screen_TachoBar3.set_size(231,78)
screen_TachoBar3.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp531143246.png','rb') as f:
        screen_TachoBar3_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp531143246.png')
    sys.exit()

screen_TachoBar3_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar3_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar3_img_data
})

screen_TachoBar3.set_src(screen_TachoBar3_img)
screen_TachoBar3.set_pivot(0,0)
screen_TachoBar3.set_angle(0)
# create style style_screen_tachobar3_main_main_default
style_screen_tachobar3_main_main_default = lv.style_t()
style_screen_tachobar3_main_main_default.init()
style_screen_tachobar3_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar3_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar3_main_main_default.set_img_opa(0)

# add style for screen_TachoBar3
screen_TachoBar3.add_style(style_screen_tachobar3_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar3_0 = lv.img(screen)
screen_TachoBar3_0.set_pos(3,8)
screen_TachoBar3_0.set_size(231,78)
screen_TachoBar3_0.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp562163053.png','rb') as f:
        screen_TachoBar3_0_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp562163053.png')
    sys.exit()

screen_TachoBar3_0_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar3_0_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar3_0_img_data
})

screen_TachoBar3_0.set_src(screen_TachoBar3_0_img)
screen_TachoBar3_0.set_pivot(0,0)
screen_TachoBar3_0.set_angle(0)
# create style style_screen_tachobar3_0_main_main_default
style_screen_tachobar3_0_main_main_default = lv.style_t()
style_screen_tachobar3_0_main_main_default.init()
style_screen_tachobar3_0_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar3_0_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar3_0_main_main_default.set_img_opa(0)

# add style for screen_TachoBar3_0
screen_TachoBar3_0.add_style(style_screen_tachobar3_0_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar3_1 = lv.img(screen)
screen_TachoBar3_1.set_pos(3,8)
screen_TachoBar3_1.set_size(231,78)
screen_TachoBar3_1.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp593182860.png','rb') as f:
        screen_TachoBar3_1_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp593182860.png')
    sys.exit()

screen_TachoBar3_1_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar3_1_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar3_1_img_data
})

screen_TachoBar3_1.set_src(screen_TachoBar3_1_img)
screen_TachoBar3_1.set_pivot(0,0)
screen_TachoBar3_1.set_angle(0)
# create style style_screen_tachobar3_1_main_main_default
style_screen_tachobar3_1_main_main_default = lv.style_t()
style_screen_tachobar3_1_main_main_default.init()
style_screen_tachobar3_1_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar3_1_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar3_1_main_main_default.set_img_opa(0)

# add style for screen_TachoBar3_1
screen_TachoBar3_1.add_style(style_screen_tachobar3_1_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar3_2 = lv.img(screen)
screen_TachoBar3_2.set_pos(3,8)
screen_TachoBar3_2.set_size(231,78)
screen_TachoBar3_2.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp624202667.png','rb') as f:
        screen_TachoBar3_2_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp624202667.png')
    sys.exit()

screen_TachoBar3_2_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar3_2_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar3_2_img_data
})

screen_TachoBar3_2.set_src(screen_TachoBar3_2_img)
screen_TachoBar3_2.set_pivot(0,0)
screen_TachoBar3_2.set_angle(0)
# create style style_screen_tachobar3_2_main_main_default
style_screen_tachobar3_2_main_main_default = lv.style_t()
style_screen_tachobar3_2_main_main_default.init()
style_screen_tachobar3_2_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar3_2_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar3_2_main_main_default.set_img_opa(0)

# add style for screen_TachoBar3_2
screen_TachoBar3_2.add_style(style_screen_tachobar3_2_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar4 = lv.img(screen)
screen_TachoBar4.set_pos(3,8)
screen_TachoBar4.set_size(231,78)
screen_TachoBar4.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp655222474.png','rb') as f:
        screen_TachoBar4_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp655222474.png')
    sys.exit()

screen_TachoBar4_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar4_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar4_img_data
})

screen_TachoBar4.set_src(screen_TachoBar4_img)
screen_TachoBar4.set_pivot(0,0)
screen_TachoBar4.set_angle(0)
# create style style_screen_tachobar4_main_main_default
style_screen_tachobar4_main_main_default = lv.style_t()
style_screen_tachobar4_main_main_default.init()
style_screen_tachobar4_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar4_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar4_main_main_default.set_img_opa(0)

# add style for screen_TachoBar4
screen_TachoBar4.add_style(style_screen_tachobar4_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar4_0 = lv.img(screen)
screen_TachoBar4_0.set_pos(3,8)
screen_TachoBar4_0.set_size(231,78)
screen_TachoBar4_0.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp686242281.png','rb') as f:
        screen_TachoBar4_0_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp686242281.png')
    sys.exit()

screen_TachoBar4_0_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar4_0_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar4_0_img_data
})

screen_TachoBar4_0.set_src(screen_TachoBar4_0_img)
screen_TachoBar4_0.set_pivot(0,0)
screen_TachoBar4_0.set_angle(0)
# create style style_screen_tachobar4_0_main_main_default
style_screen_tachobar4_0_main_main_default = lv.style_t()
style_screen_tachobar4_0_main_main_default.init()
style_screen_tachobar4_0_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar4_0_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar4_0_main_main_default.set_img_opa(0)

# add style for screen_TachoBar4_0
screen_TachoBar4_0.add_style(style_screen_tachobar4_0_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar4_1 = lv.img(screen)
screen_TachoBar4_1.set_pos(3,8)
screen_TachoBar4_1.set_size(231,78)
screen_TachoBar4_1.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp717262088.png','rb') as f:
        screen_TachoBar4_1_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp717262088.png')
    sys.exit()

screen_TachoBar4_1_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar4_1_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar4_1_img_data
})

screen_TachoBar4_1.set_src(screen_TachoBar4_1_img)
screen_TachoBar4_1.set_pivot(0,0)
screen_TachoBar4_1.set_angle(0)
# create style style_screen_tachobar4_1_main_main_default
style_screen_tachobar4_1_main_main_default = lv.style_t()
style_screen_tachobar4_1_main_main_default.init()
style_screen_tachobar4_1_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar4_1_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar4_1_main_main_default.set_img_opa(0)

# add style for screen_TachoBar4_1
screen_TachoBar4_1.add_style(style_screen_tachobar4_1_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar4_2 = lv.img(screen)
screen_TachoBar4_2.set_pos(3,8)
screen_TachoBar4_2.set_size(231,78)
screen_TachoBar4_2.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp748281895.png','rb') as f:
        screen_TachoBar4_2_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp748281895.png')
    sys.exit()

screen_TachoBar4_2_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar4_2_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar4_2_img_data
})

screen_TachoBar4_2.set_src(screen_TachoBar4_2_img)
screen_TachoBar4_2.set_pivot(0,0)
screen_TachoBar4_2.set_angle(0)
# create style style_screen_tachobar4_2_main_main_default
style_screen_tachobar4_2_main_main_default = lv.style_t()
style_screen_tachobar4_2_main_main_default.init()
style_screen_tachobar4_2_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar4_2_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar4_2_main_main_default.set_img_opa(0)

# add style for screen_TachoBar4_2
screen_TachoBar4_2.add_style(style_screen_tachobar4_2_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar5 = lv.img(screen)
screen_TachoBar5.set_pos(3,8)
screen_TachoBar5.set_size(231,78)
screen_TachoBar5.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp1430717649.png','rb') as f:
        screen_TachoBar5_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp1430717649.png')
    sys.exit()

screen_TachoBar5_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar5_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar5_img_data
})

screen_TachoBar5.set_src(screen_TachoBar5_img)
screen_TachoBar5.set_pivot(0,0)
screen_TachoBar5.set_angle(0)
# create style style_screen_tachobar5_main_main_default
style_screen_tachobar5_main_main_default = lv.style_t()
style_screen_tachobar5_main_main_default.init()
style_screen_tachobar5_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar5_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar5_main_main_default.set_img_opa(0)

# add style for screen_TachoBar5
screen_TachoBar5.add_style(style_screen_tachobar5_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar5_0 = lv.img(screen)
screen_TachoBar5_0.set_pos(3,8)
screen_TachoBar5_0.set_size(231,78)
screen_TachoBar5_0.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp1461737456.png','rb') as f:
        screen_TachoBar5_0_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp1461737456.png')
    sys.exit()

screen_TachoBar5_0_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar5_0_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar5_0_img_data
})

screen_TachoBar5_0.set_src(screen_TachoBar5_0_img)
screen_TachoBar5_0.set_pivot(0,0)
screen_TachoBar5_0.set_angle(0)
# create style style_screen_tachobar5_0_main_main_default
style_screen_tachobar5_0_main_main_default = lv.style_t()
style_screen_tachobar5_0_main_main_default.init()
style_screen_tachobar5_0_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar5_0_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar5_0_main_main_default.set_img_opa(0)

# add style for screen_TachoBar5_0
screen_TachoBar5_0.add_style(style_screen_tachobar5_0_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar5_1 = lv.img(screen)
screen_TachoBar5_1.set_pos(3,8)
screen_TachoBar5_1.set_size(231,78)
screen_TachoBar5_1.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp1492757263.png','rb') as f:
        screen_TachoBar5_1_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp1492757263.png')
    sys.exit()

screen_TachoBar5_1_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar5_1_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar5_1_img_data
})

screen_TachoBar5_1.set_src(screen_TachoBar5_1_img)
screen_TachoBar5_1.set_pivot(0,0)
screen_TachoBar5_1.set_angle(0)
# create style style_screen_tachobar5_1_main_main_default
style_screen_tachobar5_1_main_main_default = lv.style_t()
style_screen_tachobar5_1_main_main_default.init()
style_screen_tachobar5_1_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar5_1_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar5_1_main_main_default.set_img_opa(0)

# add style for screen_TachoBar5_1
screen_TachoBar5_1.add_style(style_screen_tachobar5_1_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar5_2 = lv.img(screen)
screen_TachoBar5_2.set_pos(3,8)
screen_TachoBar5_2.set_size(231,78)
screen_TachoBar5_2.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp1523777070.png','rb') as f:
        screen_TachoBar5_2_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp1523777070.png')
    sys.exit()

screen_TachoBar5_2_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar5_2_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar5_2_img_data
})

screen_TachoBar5_2.set_src(screen_TachoBar5_2_img)
screen_TachoBar5_2.set_pivot(0,0)
screen_TachoBar5_2.set_angle(0)
# create style style_screen_tachobar5_2_main_main_default
style_screen_tachobar5_2_main_main_default = lv.style_t()
style_screen_tachobar5_2_main_main_default.init()
style_screen_tachobar5_2_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar5_2_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar5_2_main_main_default.set_img_opa(0)

# add style for screen_TachoBar5_2
screen_TachoBar5_2.add_style(style_screen_tachobar5_2_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar6 = lv.img(screen)
screen_TachoBar6.set_pos(3,8)
screen_TachoBar6.set_size(231,78)
screen_TachoBar6.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp1554796877.png','rb') as f:
        screen_TachoBar6_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp1554796877.png')
    sys.exit()

screen_TachoBar6_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar6_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar6_img_data
})

screen_TachoBar6.set_src(screen_TachoBar6_img)
screen_TachoBar6.set_pivot(0,0)
screen_TachoBar6.set_angle(0)
# create style style_screen_tachobar6_main_main_default
style_screen_tachobar6_main_main_default = lv.style_t()
style_screen_tachobar6_main_main_default.init()
style_screen_tachobar6_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar6_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar6_main_main_default.set_img_opa(0)

# add style for screen_TachoBar6
screen_TachoBar6.add_style(style_screen_tachobar6_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar6_0 = lv.img(screen)
screen_TachoBar6_0.set_pos(3,8)
screen_TachoBar6_0.set_size(231,78)
screen_TachoBar6_0.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp1585816684.png','rb') as f:
        screen_TachoBar6_0_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp1585816684.png')
    sys.exit()

screen_TachoBar6_0_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar6_0_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar6_0_img_data
})

screen_TachoBar6_0.set_src(screen_TachoBar6_0_img)
screen_TachoBar6_0.set_pivot(0,0)
screen_TachoBar6_0.set_angle(0)
# create style style_screen_tachobar6_0_main_main_default
style_screen_tachobar6_0_main_main_default = lv.style_t()
style_screen_tachobar6_0_main_main_default.init()
style_screen_tachobar6_0_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar6_0_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar6_0_main_main_default.set_img_opa(0)

# add style for screen_TachoBar6_0
screen_TachoBar6_0.add_style(style_screen_tachobar6_0_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar6_1 = lv.img(screen)
screen_TachoBar6_1.set_pos(3,8)
screen_TachoBar6_1.set_size(231,78)
screen_TachoBar6_1.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp1616836491.png','rb') as f:
        screen_TachoBar6_1_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp1616836491.png')
    sys.exit()

screen_TachoBar6_1_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar6_1_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar6_1_img_data
})

screen_TachoBar6_1.set_src(screen_TachoBar6_1_img)
screen_TachoBar6_1.set_pivot(0,0)
screen_TachoBar6_1.set_angle(0)
# create style style_screen_tachobar6_1_main_main_default
style_screen_tachobar6_1_main_main_default = lv.style_t()
style_screen_tachobar6_1_main_main_default.init()
style_screen_tachobar6_1_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar6_1_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar6_1_main_main_default.set_img_opa(0)

# add style for screen_TachoBar6_1
screen_TachoBar6_1.add_style(style_screen_tachobar6_1_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar6_2 = lv.img(screen)
screen_TachoBar6_2.set_pos(3,8)
screen_TachoBar6_2.set_size(231,78)
screen_TachoBar6_2.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp1647856298.png','rb') as f:
        screen_TachoBar6_2_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp1647856298.png')
    sys.exit()

screen_TachoBar6_2_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar6_2_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar6_2_img_data
})

screen_TachoBar6_2.set_src(screen_TachoBar6_2_img)
screen_TachoBar6_2.set_pivot(0,0)
screen_TachoBar6_2.set_angle(0)
# create style style_screen_tachobar6_2_main_main_default
style_screen_tachobar6_2_main_main_default = lv.style_t()
style_screen_tachobar6_2_main_main_default.init()
style_screen_tachobar6_2_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar6_2_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar6_2_main_main_default.set_img_opa(0)

# add style for screen_TachoBar6_2
screen_TachoBar6_2.add_style(style_screen_tachobar6_2_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar7 = lv.img(screen)
screen_TachoBar7.set_pos(3,8)
screen_TachoBar7.set_size(231,78)
screen_TachoBar7.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp1678876105.png','rb') as f:
        screen_TachoBar7_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp1678876105.png')
    sys.exit()

screen_TachoBar7_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar7_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar7_img_data
})

screen_TachoBar7.set_src(screen_TachoBar7_img)
screen_TachoBar7.set_pivot(0,0)
screen_TachoBar7.set_angle(0)
# create style style_screen_tachobar7_main_main_default
style_screen_tachobar7_main_main_default = lv.style_t()
style_screen_tachobar7_main_main_default.init()
style_screen_tachobar7_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar7_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar7_main_main_default.set_img_opa(0)

# add style for screen_TachoBar7
screen_TachoBar7.add_style(style_screen_tachobar7_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar7_0 = lv.img(screen)
screen_TachoBar7_0.set_pos(3,8)
screen_TachoBar7_0.set_size(231,78)
screen_TachoBar7_0.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp1709895912.png','rb') as f:
        screen_TachoBar7_0_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp1709895912.png')
    sys.exit()

screen_TachoBar7_0_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar7_0_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar7_0_img_data
})

screen_TachoBar7_0.set_src(screen_TachoBar7_0_img)
screen_TachoBar7_0.set_pivot(0,0)
screen_TachoBar7_0.set_angle(0)
# create style style_screen_tachobar7_0_main_main_default
style_screen_tachobar7_0_main_main_default = lv.style_t()
style_screen_tachobar7_0_main_main_default.init()
style_screen_tachobar7_0_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar7_0_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar7_0_main_main_default.set_img_opa(0)

# add style for screen_TachoBar7_0
screen_TachoBar7_0.add_style(style_screen_tachobar7_0_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar7_1 = lv.img(screen)
screen_TachoBar7_1.set_pos(3,8)
screen_TachoBar7_1.set_size(231,78)
screen_TachoBar7_1.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1902635630.png','rb') as f:
        screen_TachoBar7_1_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1902635630.png')
    sys.exit()

screen_TachoBar7_1_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar7_1_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar7_1_img_data
})

screen_TachoBar7_1.set_src(screen_TachoBar7_1_img)
screen_TachoBar7_1.set_pivot(0,0)
screen_TachoBar7_1.set_angle(0)
# create style style_screen_tachobar7_1_main_main_default
style_screen_tachobar7_1_main_main_default = lv.style_t()
style_screen_tachobar7_1_main_main_default.init()
style_screen_tachobar7_1_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar7_1_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar7_1_main_main_default.set_img_opa(0)

# add style for screen_TachoBar7_1
screen_TachoBar7_1.add_style(style_screen_tachobar7_1_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar7_2 = lv.img(screen)
screen_TachoBar7_2.set_pos(3,8)
screen_TachoBar7_2.set_size(231,78)
screen_TachoBar7_2.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1871615823.png','rb') as f:
        screen_TachoBar7_2_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1871615823.png')
    sys.exit()

screen_TachoBar7_2_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar7_2_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar7_2_img_data
})

screen_TachoBar7_2.set_src(screen_TachoBar7_2_img)
screen_TachoBar7_2.set_pivot(0,0)
screen_TachoBar7_2.set_angle(0)
# create style style_screen_tachobar7_2_main_main_default
style_screen_tachobar7_2_main_main_default = lv.style_t()
style_screen_tachobar7_2_main_main_default.init()
style_screen_tachobar7_2_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar7_2_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar7_2_main_main_default.set_img_opa(0)

# add style for screen_TachoBar7_2
screen_TachoBar7_2.add_style(style_screen_tachobar7_2_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar8 = lv.img(screen)
screen_TachoBar8.set_pos(3,8)
screen_TachoBar8.set_size(231,78)
screen_TachoBar8.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1840596016.png','rb') as f:
        screen_TachoBar8_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1840596016.png')
    sys.exit()

screen_TachoBar8_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar8_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar8_img_data
})

screen_TachoBar8.set_src(screen_TachoBar8_img)
screen_TachoBar8.set_pivot(0,0)
screen_TachoBar8.set_angle(0)
# create style style_screen_tachobar8_main_main_default
style_screen_tachobar8_main_main_default = lv.style_t()
style_screen_tachobar8_main_main_default.init()
style_screen_tachobar8_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar8_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar8_main_main_default.set_img_opa(0)

# add style for screen_TachoBar8
screen_TachoBar8.add_style(style_screen_tachobar8_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_CLK_Hour_up_Arrow = lv.imgbtn(screen)
screen_CLK_Hour_up_Arrow.set_pos(102,176)
screen_CLK_Hour_up_Arrow.set_size(9,9)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1360374465.png','rb') as f:
        screen_CLK_Hour_up_Arrow_imgReleased_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1360374465.png')
    sys.exit()

screen_CLK_Hour_up_Arrow_imgReleased = lv.img_dsc_t({
  'data_size': len(screen_CLK_Hour_up_Arrow_imgReleased_data),
  'header': {'always_zero': 0, 'w': 9, 'h': 9, 'cf': lv.img.CF.TRUE_COLOR},
  'data': screen_CLK_Hour_up_Arrow_imgReleased_data
})
screen_CLK_Hour_up_Arrow.set_src(lv.imgbtn.STATE.RELEASED, screen_CLK_Hour_up_Arrow_imgReleased, None, None)

try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-39623842.png','rb') as f:
        screen_CLK_Hour_up_Arrow_imgPressed_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-39623842.png')
    sys.exit()

screen_CLK_Hour_up_Arrow_imgPressed = lv.img_dsc_t({
  'data_size': len(screen_CLK_Hour_up_Arrow_imgPressed_data),
  'header': {'always_zero': 0, 'w': 9, 'h': 9, 'cf': lv.img.CF.TRUE_COLOR},
  'data': screen_CLK_Hour_up_Arrow_imgPressed_data
})
screen_CLK_Hour_up_Arrow.set_src(lv.imgbtn.STATE.PRESSED, screen_CLK_Hour_up_Arrow_imgPressed, None, None)




screen_CLK_Hour_up_Arrow.add_flag(lv.obj.FLAG.CHECKABLE)
# create style style_screen_clk_hour_up_arrow_main_main_default
style_screen_clk_hour_up_arrow_main_main_default = lv.style_t()
style_screen_clk_hour_up_arrow_main_main_default.init()
style_screen_clk_hour_up_arrow_main_main_default.set_text_color(lv.color_make(0x00,0x00,0x00))
try:
    style_screen_clk_hour_up_arrow_main_main_default.set_text_font(lv.font_simsun_12)
except AttributeError:
    try:
        style_screen_clk_hour_up_arrow_main_main_default.set_text_font(lv.font_montserrat_12)
    except AttributeError:
        style_screen_clk_hour_up_arrow_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_clk_hour_up_arrow_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_clk_hour_up_arrow_main_main_default.set_img_recolor_opa(0)
style_screen_clk_hour_up_arrow_main_main_default.set_img_opa(255)

# add style for screen_CLK_Hour_up_Arrow
screen_CLK_Hour_up_Arrow.add_style(style_screen_clk_hour_up_arrow_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_screen_clk_hour_up_arrow_main_main_pressed
style_screen_clk_hour_up_arrow_main_main_pressed = lv.style_t()
style_screen_clk_hour_up_arrow_main_main_pressed.init()
style_screen_clk_hour_up_arrow_main_main_pressed.set_text_color(lv.color_make(0xFF,0x33,0xFF))
try:
    style_screen_clk_hour_up_arrow_main_main_pressed.set_text_font(lv.font_simsun_16)
except AttributeError:
    try:
        style_screen_clk_hour_up_arrow_main_main_pressed.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_screen_clk_hour_up_arrow_main_main_pressed.set_text_font(lv.font_montserrat_16)
style_screen_clk_hour_up_arrow_main_main_pressed.set_img_recolor(lv.color_make(0x00,0x00,0x00))
style_screen_clk_hour_up_arrow_main_main_pressed.set_img_recolor_opa(0)

# add style for screen_CLK_Hour_up_Arrow
screen_CLK_Hour_up_Arrow.add_style(style_screen_clk_hour_up_arrow_main_main_pressed, lv.PART.MAIN|lv.STATE.PRESSED)

# create style style_screen_clk_hour_up_arrow_main_main_checked
style_screen_clk_hour_up_arrow_main_main_checked = lv.style_t()
style_screen_clk_hour_up_arrow_main_main_checked.init()
style_screen_clk_hour_up_arrow_main_main_checked.set_text_color(lv.color_make(0xFF,0x33,0xFF))
try:
    style_screen_clk_hour_up_arrow_main_main_checked.set_text_font(lv.font_simsun_16)
except AttributeError:
    try:
        style_screen_clk_hour_up_arrow_main_main_checked.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_screen_clk_hour_up_arrow_main_main_checked.set_text_font(lv.font_montserrat_16)
style_screen_clk_hour_up_arrow_main_main_checked.set_img_recolor(lv.color_make(0x00,0x00,0x00))
style_screen_clk_hour_up_arrow_main_main_checked.set_img_recolor_opa(0)

# add style for screen_CLK_Hour_up_Arrow
screen_CLK_Hour_up_Arrow.add_style(style_screen_clk_hour_up_arrow_main_main_checked, lv.PART.MAIN|lv.STATE.CHECKED)

screen_CLK_Hour_Down_Arrow = lv.imgbtn(screen)
screen_CLK_Hour_Down_Arrow.set_pos(102,238)
screen_CLK_Hour_Down_Arrow.set_size(9,9)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1779687098.png','rb') as f:
        screen_CLK_Hour_Down_Arrow_imgReleased_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1779687098.png')
    sys.exit()

screen_CLK_Hour_Down_Arrow_imgReleased = lv.img_dsc_t({
  'data_size': len(screen_CLK_Hour_Down_Arrow_imgReleased_data),
  'header': {'always_zero': 0, 'w': 9, 'h': 9, 'cf': lv.img.CF.TRUE_COLOR},
  'data': screen_CLK_Hour_Down_Arrow_imgReleased_data
})
screen_CLK_Hour_Down_Arrow.set_src(lv.imgbtn.STATE.RELEASED, screen_CLK_Hour_Down_Arrow_imgReleased, None, None)

try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-39623842.png','rb') as f:
        screen_CLK_Hour_Down_Arrow_imgPressed_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-39623842.png')
    sys.exit()

screen_CLK_Hour_Down_Arrow_imgPressed = lv.img_dsc_t({
  'data_size': len(screen_CLK_Hour_Down_Arrow_imgPressed_data),
  'header': {'always_zero': 0, 'w': 9, 'h': 9, 'cf': lv.img.CF.TRUE_COLOR},
  'data': screen_CLK_Hour_Down_Arrow_imgPressed_data
})
screen_CLK_Hour_Down_Arrow.set_src(lv.imgbtn.STATE.PRESSED, screen_CLK_Hour_Down_Arrow_imgPressed, None, None)




screen_CLK_Hour_Down_Arrow.add_flag(lv.obj.FLAG.CHECKABLE)
# create style style_screen_clk_hour_down_arrow_main_main_default
style_screen_clk_hour_down_arrow_main_main_default = lv.style_t()
style_screen_clk_hour_down_arrow_main_main_default.init()
style_screen_clk_hour_down_arrow_main_main_default.set_text_color(lv.color_make(0x00,0x00,0x00))
try:
    style_screen_clk_hour_down_arrow_main_main_default.set_text_font(lv.font_simsun_12)
except AttributeError:
    try:
        style_screen_clk_hour_down_arrow_main_main_default.set_text_font(lv.font_montserrat_12)
    except AttributeError:
        style_screen_clk_hour_down_arrow_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_clk_hour_down_arrow_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_clk_hour_down_arrow_main_main_default.set_img_recolor_opa(0)
style_screen_clk_hour_down_arrow_main_main_default.set_img_opa(255)

# add style for screen_CLK_Hour_Down_Arrow
screen_CLK_Hour_Down_Arrow.add_style(style_screen_clk_hour_down_arrow_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_screen_clk_hour_down_arrow_main_main_pressed
style_screen_clk_hour_down_arrow_main_main_pressed = lv.style_t()
style_screen_clk_hour_down_arrow_main_main_pressed.init()
style_screen_clk_hour_down_arrow_main_main_pressed.set_text_color(lv.color_make(0xFF,0x33,0xFF))
try:
    style_screen_clk_hour_down_arrow_main_main_pressed.set_text_font(lv.font_simsun_16)
except AttributeError:
    try:
        style_screen_clk_hour_down_arrow_main_main_pressed.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_screen_clk_hour_down_arrow_main_main_pressed.set_text_font(lv.font_montserrat_16)
style_screen_clk_hour_down_arrow_main_main_pressed.set_img_recolor(lv.color_make(0x00,0x00,0x00))
style_screen_clk_hour_down_arrow_main_main_pressed.set_img_recolor_opa(0)

# add style for screen_CLK_Hour_Down_Arrow
screen_CLK_Hour_Down_Arrow.add_style(style_screen_clk_hour_down_arrow_main_main_pressed, lv.PART.MAIN|lv.STATE.PRESSED)

# create style style_screen_clk_hour_down_arrow_main_main_checked
style_screen_clk_hour_down_arrow_main_main_checked = lv.style_t()
style_screen_clk_hour_down_arrow_main_main_checked.init()
style_screen_clk_hour_down_arrow_main_main_checked.set_text_color(lv.color_make(0xFF,0x33,0xFF))
try:
    style_screen_clk_hour_down_arrow_main_main_checked.set_text_font(lv.font_simsun_16)
except AttributeError:
    try:
        style_screen_clk_hour_down_arrow_main_main_checked.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_screen_clk_hour_down_arrow_main_main_checked.set_text_font(lv.font_montserrat_16)
style_screen_clk_hour_down_arrow_main_main_checked.set_img_recolor(lv.color_make(0x00,0x00,0x00))
style_screen_clk_hour_down_arrow_main_main_checked.set_img_recolor_opa(0)

# add style for screen_CLK_Hour_Down_Arrow
screen_CLK_Hour_Down_Arrow.add_style(style_screen_clk_hour_down_arrow_main_main_checked, lv.PART.MAIN|lv.STATE.CHECKED)

screen_CLK_Min_Up_Arrow = lv.imgbtn(screen)
screen_CLK_Min_Up_Arrow.set_pos(128,176)
screen_CLK_Min_Up_Arrow.set_size(9,9)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1360374465.png','rb') as f:
        screen_CLK_Min_Up_Arrow_imgReleased_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1360374465.png')
    sys.exit()

screen_CLK_Min_Up_Arrow_imgReleased = lv.img_dsc_t({
  'data_size': len(screen_CLK_Min_Up_Arrow_imgReleased_data),
  'header': {'always_zero': 0, 'w': 9, 'h': 9, 'cf': lv.img.CF.TRUE_COLOR},
  'data': screen_CLK_Min_Up_Arrow_imgReleased_data
})
screen_CLK_Min_Up_Arrow.set_src(lv.imgbtn.STATE.RELEASED, screen_CLK_Min_Up_Arrow_imgReleased, None, None)

try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-39623842.png','rb') as f:
        screen_CLK_Min_Up_Arrow_imgPressed_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-39623842.png')
    sys.exit()

screen_CLK_Min_Up_Arrow_imgPressed = lv.img_dsc_t({
  'data_size': len(screen_CLK_Min_Up_Arrow_imgPressed_data),
  'header': {'always_zero': 0, 'w': 9, 'h': 9, 'cf': lv.img.CF.TRUE_COLOR},
  'data': screen_CLK_Min_Up_Arrow_imgPressed_data
})
screen_CLK_Min_Up_Arrow.set_src(lv.imgbtn.STATE.PRESSED, screen_CLK_Min_Up_Arrow_imgPressed, None, None)




screen_CLK_Min_Up_Arrow.add_flag(lv.obj.FLAG.CHECKABLE)
# create style style_screen_clk_min_up_arrow_main_main_default
style_screen_clk_min_up_arrow_main_main_default = lv.style_t()
style_screen_clk_min_up_arrow_main_main_default.init()
style_screen_clk_min_up_arrow_main_main_default.set_text_color(lv.color_make(0x00,0x00,0x00))
try:
    style_screen_clk_min_up_arrow_main_main_default.set_text_font(lv.font_simsun_12)
except AttributeError:
    try:
        style_screen_clk_min_up_arrow_main_main_default.set_text_font(lv.font_montserrat_12)
    except AttributeError:
        style_screen_clk_min_up_arrow_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_clk_min_up_arrow_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_clk_min_up_arrow_main_main_default.set_img_recolor_opa(0)
style_screen_clk_min_up_arrow_main_main_default.set_img_opa(255)

# add style for screen_CLK_Min_Up_Arrow
screen_CLK_Min_Up_Arrow.add_style(style_screen_clk_min_up_arrow_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_screen_clk_min_up_arrow_main_main_pressed
style_screen_clk_min_up_arrow_main_main_pressed = lv.style_t()
style_screen_clk_min_up_arrow_main_main_pressed.init()
style_screen_clk_min_up_arrow_main_main_pressed.set_text_color(lv.color_make(0xFF,0x33,0xFF))
try:
    style_screen_clk_min_up_arrow_main_main_pressed.set_text_font(lv.font_simsun_16)
except AttributeError:
    try:
        style_screen_clk_min_up_arrow_main_main_pressed.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_screen_clk_min_up_arrow_main_main_pressed.set_text_font(lv.font_montserrat_16)
style_screen_clk_min_up_arrow_main_main_pressed.set_img_recolor(lv.color_make(0x00,0x00,0x00))
style_screen_clk_min_up_arrow_main_main_pressed.set_img_recolor_opa(0)

# add style for screen_CLK_Min_Up_Arrow
screen_CLK_Min_Up_Arrow.add_style(style_screen_clk_min_up_arrow_main_main_pressed, lv.PART.MAIN|lv.STATE.PRESSED)

# create style style_screen_clk_min_up_arrow_main_main_checked
style_screen_clk_min_up_arrow_main_main_checked = lv.style_t()
style_screen_clk_min_up_arrow_main_main_checked.init()
style_screen_clk_min_up_arrow_main_main_checked.set_text_color(lv.color_make(0xFF,0x33,0xFF))
try:
    style_screen_clk_min_up_arrow_main_main_checked.set_text_font(lv.font_simsun_16)
except AttributeError:
    try:
        style_screen_clk_min_up_arrow_main_main_checked.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_screen_clk_min_up_arrow_main_main_checked.set_text_font(lv.font_montserrat_16)
style_screen_clk_min_up_arrow_main_main_checked.set_img_recolor(lv.color_make(0x00,0x00,0x00))
style_screen_clk_min_up_arrow_main_main_checked.set_img_recolor_opa(0)

# add style for screen_CLK_Min_Up_Arrow
screen_CLK_Min_Up_Arrow.add_style(style_screen_clk_min_up_arrow_main_main_checked, lv.PART.MAIN|lv.STATE.CHECKED)

screen_CLK_Min_Down_Arrow = lv.imgbtn(screen)
screen_CLK_Min_Down_Arrow.set_pos(128,238)
screen_CLK_Min_Down_Arrow.set_size(9,9)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1779687098.png','rb') as f:
        screen_CLK_Min_Down_Arrow_imgReleased_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1779687098.png')
    sys.exit()

screen_CLK_Min_Down_Arrow_imgReleased = lv.img_dsc_t({
  'data_size': len(screen_CLK_Min_Down_Arrow_imgReleased_data),
  'header': {'always_zero': 0, 'w': 9, 'h': 9, 'cf': lv.img.CF.TRUE_COLOR},
  'data': screen_CLK_Min_Down_Arrow_imgReleased_data
})
screen_CLK_Min_Down_Arrow.set_src(lv.imgbtn.STATE.RELEASED, screen_CLK_Min_Down_Arrow_imgReleased, None, None)

try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-39623842.png','rb') as f:
        screen_CLK_Min_Down_Arrow_imgPressed_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-39623842.png')
    sys.exit()

screen_CLK_Min_Down_Arrow_imgPressed = lv.img_dsc_t({
  'data_size': len(screen_CLK_Min_Down_Arrow_imgPressed_data),
  'header': {'always_zero': 0, 'w': 9, 'h': 9, 'cf': lv.img.CF.TRUE_COLOR},
  'data': screen_CLK_Min_Down_Arrow_imgPressed_data
})
screen_CLK_Min_Down_Arrow.set_src(lv.imgbtn.STATE.PRESSED, screen_CLK_Min_Down_Arrow_imgPressed, None, None)




screen_CLK_Min_Down_Arrow.add_flag(lv.obj.FLAG.CHECKABLE)
# create style style_screen_clk_min_down_arrow_main_main_default
style_screen_clk_min_down_arrow_main_main_default = lv.style_t()
style_screen_clk_min_down_arrow_main_main_default.init()
style_screen_clk_min_down_arrow_main_main_default.set_text_color(lv.color_make(0x00,0x00,0x00))
try:
    style_screen_clk_min_down_arrow_main_main_default.set_text_font(lv.font_simsun_12)
except AttributeError:
    try:
        style_screen_clk_min_down_arrow_main_main_default.set_text_font(lv.font_montserrat_12)
    except AttributeError:
        style_screen_clk_min_down_arrow_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_clk_min_down_arrow_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_clk_min_down_arrow_main_main_default.set_img_recolor_opa(0)
style_screen_clk_min_down_arrow_main_main_default.set_img_opa(255)

# add style for screen_CLK_Min_Down_Arrow
screen_CLK_Min_Down_Arrow.add_style(style_screen_clk_min_down_arrow_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_screen_clk_min_down_arrow_main_main_pressed
style_screen_clk_min_down_arrow_main_main_pressed = lv.style_t()
style_screen_clk_min_down_arrow_main_main_pressed.init()
style_screen_clk_min_down_arrow_main_main_pressed.set_text_color(lv.color_make(0xFF,0x33,0xFF))
try:
    style_screen_clk_min_down_arrow_main_main_pressed.set_text_font(lv.font_simsun_16)
except AttributeError:
    try:
        style_screen_clk_min_down_arrow_main_main_pressed.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_screen_clk_min_down_arrow_main_main_pressed.set_text_font(lv.font_montserrat_16)
style_screen_clk_min_down_arrow_main_main_pressed.set_img_recolor(lv.color_make(0x00,0x00,0x00))
style_screen_clk_min_down_arrow_main_main_pressed.set_img_recolor_opa(0)

# add style for screen_CLK_Min_Down_Arrow
screen_CLK_Min_Down_Arrow.add_style(style_screen_clk_min_down_arrow_main_main_pressed, lv.PART.MAIN|lv.STATE.PRESSED)

# create style style_screen_clk_min_down_arrow_main_main_checked
style_screen_clk_min_down_arrow_main_main_checked = lv.style_t()
style_screen_clk_min_down_arrow_main_main_checked.init()
style_screen_clk_min_down_arrow_main_main_checked.set_text_color(lv.color_make(0xFF,0x33,0xFF))
try:
    style_screen_clk_min_down_arrow_main_main_checked.set_text_font(lv.font_simsun_16)
except AttributeError:
    try:
        style_screen_clk_min_down_arrow_main_main_checked.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_screen_clk_min_down_arrow_main_main_checked.set_text_font(lv.font_montserrat_16)
style_screen_clk_min_down_arrow_main_main_checked.set_img_recolor(lv.color_make(0x00,0x00,0x00))
style_screen_clk_min_down_arrow_main_main_checked.set_img_recolor_opa(0)

# add style for screen_CLK_Min_Down_Arrow
screen_CLK_Min_Down_Arrow.add_style(style_screen_clk_min_down_arrow_main_main_checked, lv.PART.MAIN|lv.STATE.CHECKED)

screen_TachoBar9 = lv.img(screen)
screen_TachoBar9.set_pos(3,8)
screen_TachoBar9.set_size(231,78)
screen_TachoBar9.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1809576209.png','rb') as f:
        screen_TachoBar9_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1809576209.png')
    sys.exit()

screen_TachoBar9_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar9_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar9_img_data
})

screen_TachoBar9.set_src(screen_TachoBar9_img)
screen_TachoBar9.set_pivot(0,0)
screen_TachoBar9.set_angle(0)
# create style style_screen_tachobar9_main_main_default
style_screen_tachobar9_main_main_default = lv.style_t()
style_screen_tachobar9_main_main_default.init()
style_screen_tachobar9_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar9_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar9_main_main_default.set_img_opa(0)

# add style for screen_TachoBar9
screen_TachoBar9.add_style(style_screen_tachobar9_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar10 = lv.img(screen)
screen_TachoBar10.set_pos(3,8)
screen_TachoBar10.set_size(231,78)
screen_TachoBar10.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1778556402.png','rb') as f:
        screen_TachoBar10_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1778556402.png')
    sys.exit()

screen_TachoBar10_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar10_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar10_img_data
})

screen_TachoBar10.set_src(screen_TachoBar10_img)
screen_TachoBar10.set_pivot(0,0)
screen_TachoBar10.set_angle(0)
# create style style_screen_tachobar10_main_main_default
style_screen_tachobar10_main_main_default = lv.style_t()
style_screen_tachobar10_main_main_default.init()
style_screen_tachobar10_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar10_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar10_main_main_default.set_img_opa(0)

# add style for screen_TachoBar10
screen_TachoBar10.add_style(style_screen_tachobar10_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar11 = lv.img(screen)
screen_TachoBar11.set_pos(3,8)
screen_TachoBar11.set_size(231,78)
screen_TachoBar11.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1747536595.png','rb') as f:
        screen_TachoBar11_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1747536595.png')
    sys.exit()

screen_TachoBar11_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar11_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar11_img_data
})

screen_TachoBar11.set_src(screen_TachoBar11_img)
screen_TachoBar11.set_pivot(0,0)
screen_TachoBar11.set_angle(0)
# create style style_screen_tachobar11_main_main_default
style_screen_tachobar11_main_main_default = lv.style_t()
style_screen_tachobar11_main_main_default.init()
style_screen_tachobar11_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar11_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar11_main_main_default.set_img_opa(0)

# add style for screen_TachoBar11
screen_TachoBar11.add_style(style_screen_tachobar11_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar12 = lv.img(screen)
screen_TachoBar12.set_pos(3,8)
screen_TachoBar12.set_size(231,78)
screen_TachoBar12.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1716516788.png','rb') as f:
        screen_TachoBar12_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1716516788.png')
    sys.exit()

screen_TachoBar12_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar12_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar12_img_data
})

screen_TachoBar12.set_src(screen_TachoBar12_img)
screen_TachoBar12.set_pivot(0,0)
screen_TachoBar12.set_angle(0)
# create style style_screen_tachobar12_main_main_default
style_screen_tachobar12_main_main_default = lv.style_t()
style_screen_tachobar12_main_main_default.init()
style_screen_tachobar12_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar12_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar12_main_main_default.set_img_opa(0)

# add style for screen_TachoBar12
screen_TachoBar12.add_style(style_screen_tachobar12_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar13 = lv.img(screen)
screen_TachoBar13.set_pos(3,8)
screen_TachoBar13.set_size(231,78)
screen_TachoBar13.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1685496981.png','rb') as f:
        screen_TachoBar13_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1685496981.png')
    sys.exit()

screen_TachoBar13_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar13_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar13_img_data
})

screen_TachoBar13.set_src(screen_TachoBar13_img)
screen_TachoBar13.set_pivot(0,0)
screen_TachoBar13.set_angle(0)
# create style style_screen_tachobar13_main_main_default
style_screen_tachobar13_main_main_default = lv.style_t()
style_screen_tachobar13_main_main_default.init()
style_screen_tachobar13_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar13_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar13_main_main_default.set_img_opa(0)

# add style for screen_TachoBar13
screen_TachoBar13.add_style(style_screen_tachobar13_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar14 = lv.img(screen)
screen_TachoBar14.set_pos(3,8)
screen_TachoBar14.set_size(231,78)
screen_TachoBar14.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1654477174.png','rb') as f:
        screen_TachoBar14_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1654477174.png')
    sys.exit()

screen_TachoBar14_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar14_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar14_img_data
})

screen_TachoBar14.set_src(screen_TachoBar14_img)
screen_TachoBar14.set_pivot(0,0)
screen_TachoBar14.set_angle(0)
# create style style_screen_tachobar14_main_main_default
style_screen_tachobar14_main_main_default = lv.style_t()
style_screen_tachobar14_main_main_default.init()
style_screen_tachobar14_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar14_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar14_main_main_default.set_img_opa(0)

# add style for screen_TachoBar14
screen_TachoBar14.add_style(style_screen_tachobar14_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar15 = lv.img(screen)
screen_TachoBar15.set_pos(3,8)
screen_TachoBar15.set_size(231,78)
screen_TachoBar15.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1623457367.png','rb') as f:
        screen_TachoBar15_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1623457367.png')
    sys.exit()

screen_TachoBar15_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar15_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar15_img_data
})

screen_TachoBar15.set_src(screen_TachoBar15_img)
screen_TachoBar15.set_pivot(0,0)
screen_TachoBar15.set_angle(0)
# create style style_screen_tachobar15_main_main_default
style_screen_tachobar15_main_main_default = lv.style_t()
style_screen_tachobar15_main_main_default.init()
style_screen_tachobar15_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar15_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar15_main_main_default.set_img_opa(0)

# add style for screen_TachoBar15
screen_TachoBar15.add_style(style_screen_tachobar15_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar16 = lv.img(screen)
screen_TachoBar16.set_pos(3,8)
screen_TachoBar16.set_size(231,78)
screen_TachoBar16.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-941021613.png','rb') as f:
        screen_TachoBar16_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-941021613.png')
    sys.exit()

screen_TachoBar16_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar16_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar16_img_data
})

screen_TachoBar16.set_src(screen_TachoBar16_img)
screen_TachoBar16.set_pivot(0,0)
screen_TachoBar16.set_angle(0)
# create style style_screen_tachobar16_main_main_default
style_screen_tachobar16_main_main_default = lv.style_t()
style_screen_tachobar16_main_main_default.init()
style_screen_tachobar16_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar16_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar16_main_main_default.set_img_opa(0)

# add style for screen_TachoBar16
screen_TachoBar16.add_style(style_screen_tachobar16_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar17 = lv.img(screen)
screen_TachoBar17.set_pos(3,8)
screen_TachoBar17.set_size(231,78)
screen_TachoBar17.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-910001806.png','rb') as f:
        screen_TachoBar17_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-910001806.png')
    sys.exit()

screen_TachoBar17_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar17_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar17_img_data
})

screen_TachoBar17.set_src(screen_TachoBar17_img)
screen_TachoBar17.set_pivot(0,0)
screen_TachoBar17.set_angle(0)
# create style style_screen_tachobar17_main_main_default
style_screen_tachobar17_main_main_default = lv.style_t()
style_screen_tachobar17_main_main_default.init()
style_screen_tachobar17_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar17_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar17_main_main_default.set_img_opa(0)

# add style for screen_TachoBar17
screen_TachoBar17.add_style(style_screen_tachobar17_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar18 = lv.img(screen)
screen_TachoBar18.set_pos(3,8)
screen_TachoBar18.set_size(231,78)
screen_TachoBar18.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-878981999.png','rb') as f:
        screen_TachoBar18_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-878981999.png')
    sys.exit()

screen_TachoBar18_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar18_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar18_img_data
})

screen_TachoBar18.set_src(screen_TachoBar18_img)
screen_TachoBar18.set_pivot(0,0)
screen_TachoBar18.set_angle(0)
# create style style_screen_tachobar18_main_main_default
style_screen_tachobar18_main_main_default = lv.style_t()
style_screen_tachobar18_main_main_default.init()
style_screen_tachobar18_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar18_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar18_main_main_default.set_img_opa(0)

# add style for screen_TachoBar18
screen_TachoBar18.add_style(style_screen_tachobar18_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar19 = lv.img(screen)
screen_TachoBar19.set_pos(3,8)
screen_TachoBar19.set_size(231,78)
screen_TachoBar19.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-847962192.png','rb') as f:
        screen_TachoBar19_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-847962192.png')
    sys.exit()

screen_TachoBar19_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar19_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar19_img_data
})

screen_TachoBar19.set_src(screen_TachoBar19_img)
screen_TachoBar19.set_pivot(0,0)
screen_TachoBar19.set_angle(0)
# create style style_screen_tachobar19_main_main_default
style_screen_tachobar19_main_main_default = lv.style_t()
style_screen_tachobar19_main_main_default.init()
style_screen_tachobar19_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar19_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar19_main_main_default.set_img_opa(0)

# add style for screen_TachoBar19
screen_TachoBar19.add_style(style_screen_tachobar19_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar20 = lv.img(screen)
screen_TachoBar20.set_pos(3,8)
screen_TachoBar20.set_size(231,78)
screen_TachoBar20.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-816942385.png','rb') as f:
        screen_TachoBar20_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-816942385.png')
    sys.exit()

screen_TachoBar20_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar20_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar20_img_data
})

screen_TachoBar20.set_src(screen_TachoBar20_img)
screen_TachoBar20.set_pivot(0,0)
screen_TachoBar20.set_angle(0)
# create style style_screen_tachobar20_main_main_default
style_screen_tachobar20_main_main_default = lv.style_t()
style_screen_tachobar20_main_main_default.init()
style_screen_tachobar20_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar20_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar20_main_main_default.set_img_opa(0)

# add style for screen_TachoBar20
screen_TachoBar20.add_style(style_screen_tachobar20_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar21 = lv.img(screen)
screen_TachoBar21.set_pos(3,8)
screen_TachoBar21.set_size(231,78)
screen_TachoBar21.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-785922578.png','rb') as f:
        screen_TachoBar21_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-785922578.png')
    sys.exit()

screen_TachoBar21_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar21_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar21_img_data
})

screen_TachoBar21.set_src(screen_TachoBar21_img)
screen_TachoBar21.set_pivot(0,0)
screen_TachoBar21.set_angle(0)
# create style style_screen_tachobar21_main_main_default
style_screen_tachobar21_main_main_default = lv.style_t()
style_screen_tachobar21_main_main_default.init()
style_screen_tachobar21_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar21_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar21_main_main_default.set_img_opa(0)

# add style for screen_TachoBar21
screen_TachoBar21.add_style(style_screen_tachobar21_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar22 = lv.img(screen)
screen_TachoBar22.set_pos(3,8)
screen_TachoBar22.set_size(231,78)
screen_TachoBar22.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-754902771.png','rb') as f:
        screen_TachoBar22_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-754902771.png')
    sys.exit()

screen_TachoBar22_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar22_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar22_img_data
})

screen_TachoBar22.set_src(screen_TachoBar22_img)
screen_TachoBar22.set_pivot(0,0)
screen_TachoBar22.set_angle(0)
# create style style_screen_tachobar22_main_main_default
style_screen_tachobar22_main_main_default = lv.style_t()
style_screen_tachobar22_main_main_default.init()
style_screen_tachobar22_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar22_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar22_main_main_default.set_img_opa(0)

# add style for screen_TachoBar22
screen_TachoBar22.add_style(style_screen_tachobar22_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar23 = lv.img(screen)
screen_TachoBar23.set_pos(3,8)
screen_TachoBar23.set_size(231,78)
screen_TachoBar23.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-723882964.png','rb') as f:
        screen_TachoBar23_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-723882964.png')
    sys.exit()

screen_TachoBar23_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar23_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar23_img_data
})

screen_TachoBar23.set_src(screen_TachoBar23_img)
screen_TachoBar23.set_pivot(0,0)
screen_TachoBar23.set_angle(0)
# create style style_screen_tachobar23_main_main_default
style_screen_tachobar23_main_main_default = lv.style_t()
style_screen_tachobar23_main_main_default.init()
style_screen_tachobar23_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar23_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar23_main_main_default.set_img_opa(0)

# add style for screen_TachoBar23
screen_TachoBar23.add_style(style_screen_tachobar23_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar24 = lv.img(screen)
screen_TachoBar24.set_pos(3,8)
screen_TachoBar24.set_size(231,78)
screen_TachoBar24.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-692863157.png','rb') as f:
        screen_TachoBar24_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-692863157.png')
    sys.exit()

screen_TachoBar24_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar24_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar24_img_data
})

screen_TachoBar24.set_src(screen_TachoBar24_img)
screen_TachoBar24.set_pivot(0,0)
screen_TachoBar24.set_angle(0)
# create style style_screen_tachobar24_main_main_default
style_screen_tachobar24_main_main_default = lv.style_t()
style_screen_tachobar24_main_main_default.init()
style_screen_tachobar24_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar24_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar24_main_main_default.set_img_opa(0)

# add style for screen_TachoBar24
screen_TachoBar24.add_style(style_screen_tachobar24_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar25 = lv.img(screen)
screen_TachoBar25.set_pos(3,8)
screen_TachoBar25.set_size(231,78)
screen_TachoBar25.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-661843350.png','rb') as f:
        screen_TachoBar25_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-661843350.png')
    sys.exit()

screen_TachoBar25_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar25_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar25_img_data
})

screen_TachoBar25.set_src(screen_TachoBar25_img)
screen_TachoBar25.set_pivot(0,0)
screen_TachoBar25.set_angle(0)
# create style style_screen_tachobar25_main_main_default
style_screen_tachobar25_main_main_default = lv.style_t()
style_screen_tachobar25_main_main_default.init()
style_screen_tachobar25_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar25_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar25_main_main_default.set_img_opa(0)

# add style for screen_TachoBar25
screen_TachoBar25.add_style(style_screen_tachobar25_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar26 = lv.img(screen)
screen_TachoBar26.set_pos(3,8)
screen_TachoBar26.set_size(231,78)
screen_TachoBar26.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp20592404.png','rb') as f:
        screen_TachoBar26_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp20592404.png')
    sys.exit()

screen_TachoBar26_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar26_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar26_img_data
})

screen_TachoBar26.set_src(screen_TachoBar26_img)
screen_TachoBar26.set_pivot(0,0)
screen_TachoBar26.set_angle(0)
# create style style_screen_tachobar26_main_main_default
style_screen_tachobar26_main_main_default = lv.style_t()
style_screen_tachobar26_main_main_default.init()
style_screen_tachobar26_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar26_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar26_main_main_default.set_img_opa(0)

# add style for screen_TachoBar26
screen_TachoBar26.add_style(style_screen_tachobar26_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar27 = lv.img(screen)
screen_TachoBar27.set_pos(3,8)
screen_TachoBar27.set_size(231,78)
screen_TachoBar27.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp51612211.png','rb') as f:
        screen_TachoBar27_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp51612211.png')
    sys.exit()

screen_TachoBar27_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar27_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar27_img_data
})

screen_TachoBar27.set_src(screen_TachoBar27_img)
screen_TachoBar27.set_pivot(0,0)
screen_TachoBar27.set_angle(0)
# create style style_screen_tachobar27_main_main_default
style_screen_tachobar27_main_main_default = lv.style_t()
style_screen_tachobar27_main_main_default.init()
style_screen_tachobar27_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar27_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar27_main_main_default.set_img_opa(0)

# add style for screen_TachoBar27
screen_TachoBar27.add_style(style_screen_tachobar27_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar28 = lv.img(screen)
screen_TachoBar28.set_pos(3,8)
screen_TachoBar28.set_size(231,78)
screen_TachoBar28.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp82632018.png','rb') as f:
        screen_TachoBar28_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp82632018.png')
    sys.exit()

screen_TachoBar28_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar28_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar28_img_data
})

screen_TachoBar28.set_src(screen_TachoBar28_img)
screen_TachoBar28.set_pivot(0,0)
screen_TachoBar28.set_angle(0)
# create style style_screen_tachobar28_main_main_default
style_screen_tachobar28_main_main_default = lv.style_t()
style_screen_tachobar28_main_main_default.init()
style_screen_tachobar28_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar28_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar28_main_main_default.set_img_opa(0)

# add style for screen_TachoBar28
screen_TachoBar28.add_style(style_screen_tachobar28_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar29 = lv.img(screen)
screen_TachoBar29.set_pos(3,8)
screen_TachoBar29.set_size(231,78)
screen_TachoBar29.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp113651825.png','rb') as f:
        screen_TachoBar29_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp113651825.png')
    sys.exit()

screen_TachoBar29_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar29_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar29_img_data
})

screen_TachoBar29.set_src(screen_TachoBar29_img)
screen_TachoBar29.set_pivot(0,0)
screen_TachoBar29.set_angle(0)
# create style style_screen_tachobar29_main_main_default
style_screen_tachobar29_main_main_default = lv.style_t()
style_screen_tachobar29_main_main_default.init()
style_screen_tachobar29_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar29_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar29_main_main_default.set_img_opa(0)

# add style for screen_TachoBar29
screen_TachoBar29.add_style(style_screen_tachobar29_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar30 = lv.img(screen)
screen_TachoBar30.set_pos(3,8)
screen_TachoBar30.set_size(231,78)
screen_TachoBar30.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp144671632.png','rb') as f:
        screen_TachoBar30_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp144671632.png')
    sys.exit()

screen_TachoBar30_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar30_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar30_img_data
})

screen_TachoBar30.set_src(screen_TachoBar30_img)
screen_TachoBar30.set_pivot(0,0)
screen_TachoBar30.set_angle(0)
# create style style_screen_tachobar30_main_main_default
style_screen_tachobar30_main_main_default = lv.style_t()
style_screen_tachobar30_main_main_default.init()
style_screen_tachobar30_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar30_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar30_main_main_default.set_img_opa(0)

# add style for screen_TachoBar30
screen_TachoBar30.add_style(style_screen_tachobar30_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar31 = lv.img(screen)
screen_TachoBar31.set_pos(3,8)
screen_TachoBar31.set_size(231,78)
screen_TachoBar31.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp175691439.png','rb') as f:
        screen_TachoBar31_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp175691439.png')
    sys.exit()

screen_TachoBar31_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar31_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar31_img_data
})

screen_TachoBar31.set_src(screen_TachoBar31_img)
screen_TachoBar31.set_pivot(0,0)
screen_TachoBar31.set_angle(0)
# create style style_screen_tachobar31_main_main_default
style_screen_tachobar31_main_main_default = lv.style_t()
style_screen_tachobar31_main_main_default.init()
style_screen_tachobar31_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar31_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar31_main_main_default.set_img_opa(0)

# add style for screen_TachoBar31
screen_TachoBar31.add_style(style_screen_tachobar31_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar32 = lv.img(screen)
screen_TachoBar32.set_pos(3,8)
screen_TachoBar32.set_size(231,78)
screen_TachoBar32.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp206711246.png','rb') as f:
        screen_TachoBar32_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp206711246.png')
    sys.exit()

screen_TachoBar32_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar32_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar32_img_data
})

screen_TachoBar32.set_src(screen_TachoBar32_img)
screen_TachoBar32.set_pivot(0,0)
screen_TachoBar32.set_angle(0)
# create style style_screen_tachobar32_main_main_default
style_screen_tachobar32_main_main_default = lv.style_t()
style_screen_tachobar32_main_main_default.init()
style_screen_tachobar32_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar32_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar32_main_main_default.set_img_opa(0)

# add style for screen_TachoBar32
screen_TachoBar32.add_style(style_screen_tachobar32_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar33 = lv.img(screen)
screen_TachoBar33.set_pos(3,8)
screen_TachoBar33.set_size(231,78)
screen_TachoBar33.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp237731053.png','rb') as f:
        screen_TachoBar33_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp237731053.png')
    sys.exit()

screen_TachoBar33_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar33_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar33_img_data
})

screen_TachoBar33.set_src(screen_TachoBar33_img)
screen_TachoBar33.set_pivot(0,0)
screen_TachoBar33.set_angle(0)
# create style style_screen_tachobar33_main_main_default
style_screen_tachobar33_main_main_default = lv.style_t()
style_screen_tachobar33_main_main_default.init()
style_screen_tachobar33_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar33_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar33_main_main_default.set_img_opa(0)

# add style for screen_TachoBar33
screen_TachoBar33.add_style(style_screen_tachobar33_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar34 = lv.img(screen)
screen_TachoBar34.set_pos(3,8)
screen_TachoBar34.set_size(231,78)
screen_TachoBar34.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp268750860.png','rb') as f:
        screen_TachoBar34_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp268750860.png')
    sys.exit()

screen_TachoBar34_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar34_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar34_img_data
})

screen_TachoBar34.set_src(screen_TachoBar34_img)
screen_TachoBar34.set_pivot(0,0)
screen_TachoBar34.set_angle(0)
# create style style_screen_tachobar34_main_main_default
style_screen_tachobar34_main_main_default = lv.style_t()
style_screen_tachobar34_main_main_default.init()
style_screen_tachobar34_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar34_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar34_main_main_default.set_img_opa(0)

# add style for screen_TachoBar34
screen_TachoBar34.add_style(style_screen_tachobar34_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar35 = lv.img(screen)
screen_TachoBar35.set_pos(3,8)
screen_TachoBar35.set_size(231,78)
screen_TachoBar35.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp299770667.png','rb') as f:
        screen_TachoBar35_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp299770667.png')
    sys.exit()

screen_TachoBar35_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar35_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar35_img_data
})

screen_TachoBar35.set_src(screen_TachoBar35_img)
screen_TachoBar35.set_pivot(0,0)
screen_TachoBar35.set_angle(0)
# create style style_screen_tachobar35_main_main_default
style_screen_tachobar35_main_main_default = lv.style_t()
style_screen_tachobar35_main_main_default.init()
style_screen_tachobar35_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar35_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar35_main_main_default.set_img_opa(0)

# add style for screen_TachoBar35
screen_TachoBar35.add_style(style_screen_tachobar35_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar36 = lv.img(screen)
screen_TachoBar36.set_pos(3,8)
screen_TachoBar36.set_size(231,78)
screen_TachoBar36.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp982206421.png','rb') as f:
        screen_TachoBar36_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp982206421.png')
    sys.exit()

screen_TachoBar36_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar36_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar36_img_data
})

screen_TachoBar36.set_src(screen_TachoBar36_img)
screen_TachoBar36.set_pivot(0,0)
screen_TachoBar36.set_angle(0)
# create style style_screen_tachobar36_main_main_default
style_screen_tachobar36_main_main_default = lv.style_t()
style_screen_tachobar36_main_main_default.init()
style_screen_tachobar36_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar36_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar36_main_main_default.set_img_opa(0)

# add style for screen_TachoBar36
screen_TachoBar36.add_style(style_screen_tachobar36_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar37 = lv.img(screen)
screen_TachoBar37.set_pos(3,8)
screen_TachoBar37.set_size(231,78)
screen_TachoBar37.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp1013226228.png','rb') as f:
        screen_TachoBar37_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp1013226228.png')
    sys.exit()

screen_TachoBar37_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar37_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar37_img_data
})

screen_TachoBar37.set_src(screen_TachoBar37_img)
screen_TachoBar37.set_pivot(0,0)
screen_TachoBar37.set_angle(0)
# create style style_screen_tachobar37_main_main_default
style_screen_tachobar37_main_main_default = lv.style_t()
style_screen_tachobar37_main_main_default.init()
style_screen_tachobar37_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar37_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar37_main_main_default.set_img_opa(0)

# add style for screen_TachoBar37
screen_TachoBar37.add_style(style_screen_tachobar37_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar38 = lv.img(screen)
screen_TachoBar38.set_pos(3,8)
screen_TachoBar38.set_size(231,78)
screen_TachoBar38.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp1044246035.png','rb') as f:
        screen_TachoBar38_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp1044246035.png')
    sys.exit()

screen_TachoBar38_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar38_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar38_img_data
})

screen_TachoBar38.set_src(screen_TachoBar38_img)
screen_TachoBar38.set_pivot(0,0)
screen_TachoBar38.set_angle(0)
# create style style_screen_tachobar38_main_main_default
style_screen_tachobar38_main_main_default = lv.style_t()
style_screen_tachobar38_main_main_default.init()
style_screen_tachobar38_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar38_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar38_main_main_default.set_img_opa(0)

# add style for screen_TachoBar38
screen_TachoBar38.add_style(style_screen_tachobar38_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar39 = lv.img(screen)
screen_TachoBar39.set_pos(3,8)
screen_TachoBar39.set_size(231,78)
screen_TachoBar39.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp1075265842.png','rb') as f:
        screen_TachoBar39_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp1075265842.png')
    sys.exit()

screen_TachoBar39_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar39_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar39_img_data
})

screen_TachoBar39.set_src(screen_TachoBar39_img)
screen_TachoBar39.set_pivot(0,0)
screen_TachoBar39.set_angle(0)
# create style style_screen_tachobar39_main_main_default
style_screen_tachobar39_main_main_default = lv.style_t()
style_screen_tachobar39_main_main_default.init()
style_screen_tachobar39_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar39_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar39_main_main_default.set_img_opa(0)

# add style for screen_TachoBar39
screen_TachoBar39.add_style(style_screen_tachobar39_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar40 = lv.img(screen)
screen_TachoBar40.set_pos(3,8)
screen_TachoBar40.set_size(231,78)
screen_TachoBar40.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp1106285649.png','rb') as f:
        screen_TachoBar40_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp1106285649.png')
    sys.exit()

screen_TachoBar40_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar40_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar40_img_data
})

screen_TachoBar40.set_src(screen_TachoBar40_img)
screen_TachoBar40.set_pivot(0,0)
screen_TachoBar40.set_angle(0)
# create style style_screen_tachobar40_main_main_default
style_screen_tachobar40_main_main_default = lv.style_t()
style_screen_tachobar40_main_main_default.init()
style_screen_tachobar40_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar40_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar40_main_main_default.set_img_opa(0)

# add style for screen_TachoBar40
screen_TachoBar40.add_style(style_screen_tachobar40_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar41 = lv.img(screen)
screen_TachoBar41.set_pos(3,8)
screen_TachoBar41.set_size(231,78)
screen_TachoBar41.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp1137305456.png','rb') as f:
        screen_TachoBar41_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp1137305456.png')
    sys.exit()

screen_TachoBar41_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar41_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar41_img_data
})

screen_TachoBar41.set_src(screen_TachoBar41_img)
screen_TachoBar41.set_pivot(0,0)
screen_TachoBar41.set_angle(0)
# create style style_screen_tachobar41_main_main_default
style_screen_tachobar41_main_main_default = lv.style_t()
style_screen_tachobar41_main_main_default.init()
style_screen_tachobar41_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar41_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar41_main_main_default.set_img_opa(0)

# add style for screen_TachoBar41
screen_TachoBar41.add_style(style_screen_tachobar41_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar42 = lv.img(screen)
screen_TachoBar42.set_pos(3,8)
screen_TachoBar42.set_size(231,78)
screen_TachoBar42.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp1168325263.png','rb') as f:
        screen_TachoBar42_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp1168325263.png')
    sys.exit()

screen_TachoBar42_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar42_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar42_img_data
})

screen_TachoBar42.set_src(screen_TachoBar42_img)
screen_TachoBar42.set_pivot(0,0)
screen_TachoBar42.set_angle(0)
# create style style_screen_tachobar42_main_main_default
style_screen_tachobar42_main_main_default = lv.style_t()
style_screen_tachobar42_main_main_default.init()
style_screen_tachobar42_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar42_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar42_main_main_default.set_img_opa(0)

# add style for screen_TachoBar42
screen_TachoBar42.add_style(style_screen_tachobar42_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar43 = lv.img(screen)
screen_TachoBar43.set_pos(3,8)
screen_TachoBar43.set_size(231,78)
screen_TachoBar43.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp1199345070.png','rb') as f:
        screen_TachoBar43_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp1199345070.png')
    sys.exit()

screen_TachoBar43_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar43_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar43_img_data
})

screen_TachoBar43.set_src(screen_TachoBar43_img)
screen_TachoBar43.set_pivot(0,0)
screen_TachoBar43.set_angle(0)
# create style style_screen_tachobar43_main_main_default
style_screen_tachobar43_main_main_default = lv.style_t()
style_screen_tachobar43_main_main_default.init()
style_screen_tachobar43_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar43_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar43_main_main_default.set_img_opa(0)

# add style for screen_TachoBar43
screen_TachoBar43.add_style(style_screen_tachobar43_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar44 = lv.img(screen)
screen_TachoBar44.set_pos(3,8)
screen_TachoBar44.set_size(231,78)
screen_TachoBar44.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp1230364877.png','rb') as f:
        screen_TachoBar44_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp1230364877.png')
    sys.exit()

screen_TachoBar44_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar44_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar44_img_data
})

screen_TachoBar44.set_src(screen_TachoBar44_img)
screen_TachoBar44.set_pivot(0,0)
screen_TachoBar44.set_angle(0)
# create style style_screen_tachobar44_main_main_default
style_screen_tachobar44_main_main_default = lv.style_t()
style_screen_tachobar44_main_main_default.init()
style_screen_tachobar44_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar44_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar44_main_main_default.set_img_opa(0)

# add style for screen_TachoBar44
screen_TachoBar44.add_style(style_screen_tachobar44_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar45 = lv.img(screen)
screen_TachoBar45.set_pos(3,8)
screen_TachoBar45.set_size(231,78)
screen_TachoBar45.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp1261384684.png','rb') as f:
        screen_TachoBar45_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp1261384684.png')
    sys.exit()

screen_TachoBar45_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar45_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar45_img_data
})

screen_TachoBar45.set_src(screen_TachoBar45_img)
screen_TachoBar45.set_pivot(0,0)
screen_TachoBar45.set_angle(0)
# create style style_screen_tachobar45_main_main_default
style_screen_tachobar45_main_main_default = lv.style_t()
style_screen_tachobar45_main_main_default.init()
style_screen_tachobar45_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar45_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar45_main_main_default.set_img_opa(0)

# add style for screen_TachoBar45
screen_TachoBar45.add_style(style_screen_tachobar45_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar46 = lv.img(screen)
screen_TachoBar46.set_pos(3,8)
screen_TachoBar46.set_size(231,78)
screen_TachoBar46.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp1943820438.png','rb') as f:
        screen_TachoBar46_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp1943820438.png')
    sys.exit()

screen_TachoBar46_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar46_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar46_img_data
})

screen_TachoBar46.set_src(screen_TachoBar46_img)
screen_TachoBar46.set_pivot(0,0)
screen_TachoBar46.set_angle(0)
# create style style_screen_tachobar46_main_main_default
style_screen_tachobar46_main_main_default = lv.style_t()
style_screen_tachobar46_main_main_default.init()
style_screen_tachobar46_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar46_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar46_main_main_default.set_img_opa(0)

# add style for screen_TachoBar46
screen_TachoBar46.add_style(style_screen_tachobar46_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar47 = lv.img(screen)
screen_TachoBar47.set_pos(3,8)
screen_TachoBar47.set_size(231,78)
screen_TachoBar47.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp1974840245.png','rb') as f:
        screen_TachoBar47_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp1974840245.png')
    sys.exit()

screen_TachoBar47_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar47_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar47_img_data
})

screen_TachoBar47.set_src(screen_TachoBar47_img)
screen_TachoBar47.set_pivot(0,0)
screen_TachoBar47.set_angle(0)
# create style style_screen_tachobar47_main_main_default
style_screen_tachobar47_main_main_default = lv.style_t()
style_screen_tachobar47_main_main_default.init()
style_screen_tachobar47_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar47_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar47_main_main_default.set_img_opa(0)

# add style for screen_TachoBar47
screen_TachoBar47.add_style(style_screen_tachobar47_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar48 = lv.img(screen)
screen_TachoBar48.set_pos(3,8)
screen_TachoBar48.set_size(231,78)
screen_TachoBar48.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp2005860052.png','rb') as f:
        screen_TachoBar48_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp2005860052.png')
    sys.exit()

screen_TachoBar48_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar48_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar48_img_data
})

screen_TachoBar48.set_src(screen_TachoBar48_img)
screen_TachoBar48.set_pivot(0,0)
screen_TachoBar48.set_angle(0)
# create style style_screen_tachobar48_main_main_default
style_screen_tachobar48_main_main_default = lv.style_t()
style_screen_tachobar48_main_main_default.init()
style_screen_tachobar48_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar48_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar48_main_main_default.set_img_opa(0)

# add style for screen_TachoBar48
screen_TachoBar48.add_style(style_screen_tachobar48_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar49 = lv.img(screen)
screen_TachoBar49.set_pos(3,8)
screen_TachoBar49.set_size(231,78)
screen_TachoBar49.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp2036879859.png','rb') as f:
        screen_TachoBar49_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp2036879859.png')
    sys.exit()

screen_TachoBar49_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar49_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar49_img_data
})

screen_TachoBar49.set_src(screen_TachoBar49_img)
screen_TachoBar49.set_pivot(0,0)
screen_TachoBar49.set_angle(0)
# create style style_screen_tachobar49_main_main_default
style_screen_tachobar49_main_main_default = lv.style_t()
style_screen_tachobar49_main_main_default.init()
style_screen_tachobar49_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar49_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar49_main_main_default.set_img_opa(0)

# add style for screen_TachoBar49
screen_TachoBar49.add_style(style_screen_tachobar49_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar50 = lv.img(screen)
screen_TachoBar50.set_pos(3,8)
screen_TachoBar50.set_size(231,78)
screen_TachoBar50.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp2067899666.png','rb') as f:
        screen_TachoBar50_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp2067899666.png')
    sys.exit()

screen_TachoBar50_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar50_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar50_img_data
})

screen_TachoBar50.set_src(screen_TachoBar50_img)
screen_TachoBar50.set_pivot(0,0)
screen_TachoBar50.set_angle(0)
# create style style_screen_tachobar50_main_main_default
style_screen_tachobar50_main_main_default = lv.style_t()
style_screen_tachobar50_main_main_default.init()
style_screen_tachobar50_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar50_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar50_main_main_default.set_img_opa(0)

# add style for screen_TachoBar50
screen_TachoBar50.add_style(style_screen_tachobar50_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar51 = lv.img(screen)
screen_TachoBar51.set_pos(3,8)
screen_TachoBar51.set_size(231,78)
screen_TachoBar51.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp2098919473.png','rb') as f:
        screen_TachoBar51_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp2098919473.png')
    sys.exit()

screen_TachoBar51_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar51_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar51_img_data
})

screen_TachoBar51.set_src(screen_TachoBar51_img)
screen_TachoBar51.set_pivot(0,0)
screen_TachoBar51.set_angle(0)
# create style style_screen_tachobar51_main_main_default
style_screen_tachobar51_main_main_default = lv.style_t()
style_screen_tachobar51_main_main_default.init()
style_screen_tachobar51_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar51_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar51_main_main_default.set_img_opa(0)

# add style for screen_TachoBar51
screen_TachoBar51.add_style(style_screen_tachobar51_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar52 = lv.img(screen)
screen_TachoBar52.set_pos(3,8)
screen_TachoBar52.set_size(231,78)
screen_TachoBar52.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp2129939280.png','rb') as f:
        screen_TachoBar52_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp2129939280.png')
    sys.exit()

screen_TachoBar52_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar52_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar52_img_data
})

screen_TachoBar52.set_src(screen_TachoBar52_img)
screen_TachoBar52.set_pivot(0,0)
screen_TachoBar52.set_angle(0)
# create style style_screen_tachobar52_main_main_default
style_screen_tachobar52_main_main_default = lv.style_t()
style_screen_tachobar52_main_main_default.init()
style_screen_tachobar52_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar52_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar52_main_main_default.set_img_opa(0)

# add style for screen_TachoBar52
screen_TachoBar52.add_style(style_screen_tachobar52_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar53 = lv.img(screen)
screen_TachoBar53.set_pos(3,8)
screen_TachoBar53.set_size(231,78)
screen_TachoBar53.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-2134008209.png','rb') as f:
        screen_TachoBar53_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-2134008209.png')
    sys.exit()

screen_TachoBar53_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar53_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar53_img_data
})

screen_TachoBar53.set_src(screen_TachoBar53_img)
screen_TachoBar53.set_pivot(0,0)
screen_TachoBar53.set_angle(0)
# create style style_screen_tachobar53_main_main_default
style_screen_tachobar53_main_main_default = lv.style_t()
style_screen_tachobar53_main_main_default.init()
style_screen_tachobar53_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar53_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar53_main_main_default.set_img_opa(0)

# add style for screen_TachoBar53
screen_TachoBar53.add_style(style_screen_tachobar53_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar54 = lv.img(screen)
screen_TachoBar54.set_pos(3,8)
screen_TachoBar54.set_size(231,78)
screen_TachoBar54.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-2102988402.png','rb') as f:
        screen_TachoBar54_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-2102988402.png')
    sys.exit()

screen_TachoBar54_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar54_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar54_img_data
})

screen_TachoBar54.set_src(screen_TachoBar54_img)
screen_TachoBar54.set_pivot(0,0)
screen_TachoBar54.set_angle(0)
# create style style_screen_tachobar54_main_main_default
style_screen_tachobar54_main_main_default = lv.style_t()
style_screen_tachobar54_main_main_default.init()
style_screen_tachobar54_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar54_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar54_main_main_default.set_img_opa(0)

# add style for screen_TachoBar54
screen_TachoBar54.add_style(style_screen_tachobar54_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar55 = lv.img(screen)
screen_TachoBar55.set_pos(3,8)
screen_TachoBar55.set_size(231,78)
screen_TachoBar55.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-2071968595.png','rb') as f:
        screen_TachoBar55_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-2071968595.png')
    sys.exit()

screen_TachoBar55_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar55_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar55_img_data
})

screen_TachoBar55.set_src(screen_TachoBar55_img)
screen_TachoBar55.set_pivot(0,0)
screen_TachoBar55.set_angle(0)
# create style style_screen_tachobar55_main_main_default
style_screen_tachobar55_main_main_default = lv.style_t()
style_screen_tachobar55_main_main_default.init()
style_screen_tachobar55_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar55_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar55_main_main_default.set_img_opa(0)

# add style for screen_TachoBar55
screen_TachoBar55.add_style(style_screen_tachobar55_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar56 = lv.img(screen)
screen_TachoBar56.set_pos(3,8)
screen_TachoBar56.set_size(231,78)
screen_TachoBar56.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1389532841.png','rb') as f:
        screen_TachoBar56_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1389532841.png')
    sys.exit()

screen_TachoBar56_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar56_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar56_img_data
})

screen_TachoBar56.set_src(screen_TachoBar56_img)
screen_TachoBar56.set_pivot(0,0)
screen_TachoBar56.set_angle(0)
# create style style_screen_tachobar56_main_main_default
style_screen_tachobar56_main_main_default = lv.style_t()
style_screen_tachobar56_main_main_default.init()
style_screen_tachobar56_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar56_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar56_main_main_default.set_img_opa(2)

# add style for screen_TachoBar56
screen_TachoBar56.add_style(style_screen_tachobar56_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar57 = lv.img(screen)
screen_TachoBar57.set_pos(3,8)
screen_TachoBar57.set_size(231,78)
screen_TachoBar57.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1358513034.png','rb') as f:
        screen_TachoBar57_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1358513034.png')
    sys.exit()

screen_TachoBar57_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar57_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar57_img_data
})

screen_TachoBar57.set_src(screen_TachoBar57_img)
screen_TachoBar57.set_pivot(0,0)
screen_TachoBar57.set_angle(0)
# create style style_screen_tachobar57_main_main_default
style_screen_tachobar57_main_main_default = lv.style_t()
style_screen_tachobar57_main_main_default.init()
style_screen_tachobar57_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar57_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar57_main_main_default.set_img_opa(0)

# add style for screen_TachoBar57
screen_TachoBar57.add_style(style_screen_tachobar57_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar58 = lv.img(screen)
screen_TachoBar58.set_pos(3,8)
screen_TachoBar58.set_size(231,78)
screen_TachoBar58.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1327493227.png','rb') as f:
        screen_TachoBar58_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1327493227.png')
    sys.exit()

screen_TachoBar58_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar58_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar58_img_data
})

screen_TachoBar58.set_src(screen_TachoBar58_img)
screen_TachoBar58.set_pivot(0,0)
screen_TachoBar58.set_angle(0)
# create style style_screen_tachobar58_main_main_default
style_screen_tachobar58_main_main_default = lv.style_t()
style_screen_tachobar58_main_main_default.init()
style_screen_tachobar58_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar58_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar58_main_main_default.set_img_opa(0)

# add style for screen_TachoBar58
screen_TachoBar58.add_style(style_screen_tachobar58_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar59 = lv.img(screen)
screen_TachoBar59.set_pos(3,8)
screen_TachoBar59.set_size(231,78)
screen_TachoBar59.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1296473420.png','rb') as f:
        screen_TachoBar59_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1296473420.png')
    sys.exit()

screen_TachoBar59_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar59_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar59_img_data
})

screen_TachoBar59.set_src(screen_TachoBar59_img)
screen_TachoBar59.set_pivot(0,0)
screen_TachoBar59.set_angle(0)
# create style style_screen_tachobar59_main_main_default
style_screen_tachobar59_main_main_default = lv.style_t()
style_screen_tachobar59_main_main_default.init()
style_screen_tachobar59_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar59_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar59_main_main_default.set_img_opa(0)

# add style for screen_TachoBar59
screen_TachoBar59.add_style(style_screen_tachobar59_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar60 = lv.img(screen)
screen_TachoBar60.set_pos(3,8)
screen_TachoBar60.set_size(231,78)
screen_TachoBar60.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1265453613.png','rb') as f:
        screen_TachoBar60_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1265453613.png')
    sys.exit()

screen_TachoBar60_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar60_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar60_img_data
})

screen_TachoBar60.set_src(screen_TachoBar60_img)
screen_TachoBar60.set_pivot(0,0)
screen_TachoBar60.set_angle(0)
# create style style_screen_tachobar60_main_main_default
style_screen_tachobar60_main_main_default = lv.style_t()
style_screen_tachobar60_main_main_default.init()
style_screen_tachobar60_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar60_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar60_main_main_default.set_img_opa(0)

# add style for screen_TachoBar60
screen_TachoBar60.add_style(style_screen_tachobar60_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar61 = lv.img(screen)
screen_TachoBar61.set_pos(3,8)
screen_TachoBar61.set_size(231,78)
screen_TachoBar61.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1234433806.png','rb') as f:
        screen_TachoBar61_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1234433806.png')
    sys.exit()

screen_TachoBar61_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar61_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar61_img_data
})

screen_TachoBar61.set_src(screen_TachoBar61_img)
screen_TachoBar61.set_pivot(0,0)
screen_TachoBar61.set_angle(0)
# create style style_screen_tachobar61_main_main_default
style_screen_tachobar61_main_main_default = lv.style_t()
style_screen_tachobar61_main_main_default.init()
style_screen_tachobar61_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar61_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar61_main_main_default.set_img_opa(0)

# add style for screen_TachoBar61
screen_TachoBar61.add_style(style_screen_tachobar61_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar62 = lv.img(screen)
screen_TachoBar62.set_pos(3,8)
screen_TachoBar62.set_size(231,78)
screen_TachoBar62.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1203413999.png','rb') as f:
        screen_TachoBar62_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1203413999.png')
    sys.exit()

screen_TachoBar62_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar62_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar62_img_data
})

screen_TachoBar62.set_src(screen_TachoBar62_img)
screen_TachoBar62.set_pivot(0,0)
screen_TachoBar62.set_angle(0)
# create style style_screen_tachobar62_main_main_default
style_screen_tachobar62_main_main_default = lv.style_t()
style_screen_tachobar62_main_main_default.init()
style_screen_tachobar62_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar62_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar62_main_main_default.set_img_opa(0)

# add style for screen_TachoBar62
screen_TachoBar62.add_style(style_screen_tachobar62_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar63 = lv.img(screen)
screen_TachoBar63.set_pos(3,8)
screen_TachoBar63.set_size(231,78)
screen_TachoBar63.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1172394192.png','rb') as f:
        screen_TachoBar63_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1172394192.png')
    sys.exit()

screen_TachoBar63_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar63_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar63_img_data
})

screen_TachoBar63.set_src(screen_TachoBar63_img)
screen_TachoBar63.set_pivot(0,0)
screen_TachoBar63.set_angle(0)
# create style style_screen_tachobar63_main_main_default
style_screen_tachobar63_main_main_default = lv.style_t()
style_screen_tachobar63_main_main_default.init()
style_screen_tachobar63_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar63_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar63_main_main_default.set_img_opa(0)

# add style for screen_TachoBar63
screen_TachoBar63.add_style(style_screen_tachobar63_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar64 = lv.img(screen)
screen_TachoBar64.set_pos(3,8)
screen_TachoBar64.set_size(231,78)
screen_TachoBar64.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1141374385.png','rb') as f:
        screen_TachoBar64_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1141374385.png')
    sys.exit()

screen_TachoBar64_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar64_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar64_img_data
})

screen_TachoBar64.set_src(screen_TachoBar64_img)
screen_TachoBar64.set_pivot(0,0)
screen_TachoBar64.set_angle(0)
# create style style_screen_tachobar64_main_main_default
style_screen_tachobar64_main_main_default = lv.style_t()
style_screen_tachobar64_main_main_default.init()
style_screen_tachobar64_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar64_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar64_main_main_default.set_img_opa(0)

# add style for screen_TachoBar64
screen_TachoBar64.add_style(style_screen_tachobar64_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar65 = lv.img(screen)
screen_TachoBar65.set_pos(3,8)
screen_TachoBar65.set_size(231,78)
screen_TachoBar65.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1110354578.png','rb') as f:
        screen_TachoBar65_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1110354578.png')
    sys.exit()

screen_TachoBar65_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar65_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar65_img_data
})

screen_TachoBar65.set_src(screen_TachoBar65_img)
screen_TachoBar65.set_pivot(0,0)
screen_TachoBar65.set_angle(0)
# create style style_screen_tachobar65_main_main_default
style_screen_tachobar65_main_main_default = lv.style_t()
style_screen_tachobar65_main_main_default.init()
style_screen_tachobar65_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar65_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar65_main_main_default.set_img_opa(0)

# add style for screen_TachoBar65
screen_TachoBar65.add_style(style_screen_tachobar65_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar66 = lv.img(screen)
screen_TachoBar66.set_pos(3,8)
screen_TachoBar66.set_size(231,78)
screen_TachoBar66.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-427918824.png','rb') as f:
        screen_TachoBar66_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-427918824.png')
    sys.exit()

screen_TachoBar66_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar66_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar66_img_data
})

screen_TachoBar66.set_src(screen_TachoBar66_img)
screen_TachoBar66.set_pivot(0,0)
screen_TachoBar66.set_angle(0)
# create style style_screen_tachobar66_main_main_default
style_screen_tachobar66_main_main_default = lv.style_t()
style_screen_tachobar66_main_main_default.init()
style_screen_tachobar66_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar66_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar66_main_main_default.set_img_opa(0)

# add style for screen_TachoBar66
screen_TachoBar66.add_style(style_screen_tachobar66_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar67 = lv.img(screen)
screen_TachoBar67.set_pos(3,8)
screen_TachoBar67.set_size(231,78)
screen_TachoBar67.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-396899017.png','rb') as f:
        screen_TachoBar67_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-396899017.png')
    sys.exit()

screen_TachoBar67_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar67_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar67_img_data
})

screen_TachoBar67.set_src(screen_TachoBar67_img)
screen_TachoBar67.set_pivot(0,0)
screen_TachoBar67.set_angle(0)
# create style style_screen_tachobar67_main_main_default
style_screen_tachobar67_main_main_default = lv.style_t()
style_screen_tachobar67_main_main_default.init()
style_screen_tachobar67_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar67_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar67_main_main_default.set_img_opa(0)

# add style for screen_TachoBar67
screen_TachoBar67.add_style(style_screen_tachobar67_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar68 = lv.img(screen)
screen_TachoBar68.set_pos(3,8)
screen_TachoBar68.set_size(231,78)
screen_TachoBar68.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-365879210.png','rb') as f:
        screen_TachoBar68_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-365879210.png')
    sys.exit()

screen_TachoBar68_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar68_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar68_img_data
})

screen_TachoBar68.set_src(screen_TachoBar68_img)
screen_TachoBar68.set_pivot(0,0)
screen_TachoBar68.set_angle(0)
# create style style_screen_tachobar68_main_main_default
style_screen_tachobar68_main_main_default = lv.style_t()
style_screen_tachobar68_main_main_default.init()
style_screen_tachobar68_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar68_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar68_main_main_default.set_img_opa(0)

# add style for screen_TachoBar68
screen_TachoBar68.add_style(style_screen_tachobar68_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar69 = lv.img(screen)
screen_TachoBar69.set_pos(3,8)
screen_TachoBar69.set_size(231,78)
screen_TachoBar69.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-334859403.png','rb') as f:
        screen_TachoBar69_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-334859403.png')
    sys.exit()

screen_TachoBar69_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar69_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar69_img_data
})

screen_TachoBar69.set_src(screen_TachoBar69_img)
screen_TachoBar69.set_pivot(0,0)
screen_TachoBar69.set_angle(0)
# create style style_screen_tachobar69_main_main_default
style_screen_tachobar69_main_main_default = lv.style_t()
style_screen_tachobar69_main_main_default.init()
style_screen_tachobar69_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar69_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar69_main_main_default.set_img_opa(0)

# add style for screen_TachoBar69
screen_TachoBar69.add_style(style_screen_tachobar69_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar70 = lv.img(screen)
screen_TachoBar70.set_pos(3,8)
screen_TachoBar70.set_size(231,78)
screen_TachoBar70.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-303839596.png','rb') as f:
        screen_TachoBar70_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-303839596.png')
    sys.exit()

screen_TachoBar70_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar70_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar70_img_data
})

screen_TachoBar70.set_src(screen_TachoBar70_img)
screen_TachoBar70.set_pivot(0,0)
screen_TachoBar70.set_angle(0)
# create style style_screen_tachobar70_main_main_default
style_screen_tachobar70_main_main_default = lv.style_t()
style_screen_tachobar70_main_main_default.init()
style_screen_tachobar70_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar70_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar70_main_main_default.set_img_opa(0)

# add style for screen_TachoBar70
screen_TachoBar70.add_style(style_screen_tachobar70_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar71 = lv.img(screen)
screen_TachoBar71.set_pos(3,8)
screen_TachoBar71.set_size(231,78)
screen_TachoBar71.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-272819789.png','rb') as f:
        screen_TachoBar71_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-272819789.png')
    sys.exit()

screen_TachoBar71_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar71_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar71_img_data
})

screen_TachoBar71.set_src(screen_TachoBar71_img)
screen_TachoBar71.set_pivot(0,0)
screen_TachoBar71.set_angle(0)
# create style style_screen_tachobar71_main_main_default
style_screen_tachobar71_main_main_default = lv.style_t()
style_screen_tachobar71_main_main_default.init()
style_screen_tachobar71_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar71_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar71_main_main_default.set_img_opa(0)

# add style for screen_TachoBar71
screen_TachoBar71.add_style(style_screen_tachobar71_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar72 = lv.img(screen)
screen_TachoBar72.set_pos(3,8)
screen_TachoBar72.set_size(231,78)
screen_TachoBar72.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-241799982.png','rb') as f:
        screen_TachoBar72_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-241799982.png')
    sys.exit()

screen_TachoBar72_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar72_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar72_img_data
})

screen_TachoBar72.set_src(screen_TachoBar72_img)
screen_TachoBar72.set_pivot(0,0)
screen_TachoBar72.set_angle(0)
# create style style_screen_tachobar72_main_main_default
style_screen_tachobar72_main_main_default = lv.style_t()
style_screen_tachobar72_main_main_default.init()
style_screen_tachobar72_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar72_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar72_main_main_default.set_img_opa(0)

# add style for screen_TachoBar72
screen_TachoBar72.add_style(style_screen_tachobar72_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar73 = lv.img(screen)
screen_TachoBar73.set_pos(3,8)
screen_TachoBar73.set_size(231,78)
screen_TachoBar73.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-210780175.png','rb') as f:
        screen_TachoBar73_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-210780175.png')
    sys.exit()

screen_TachoBar73_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar73_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar73_img_data
})

screen_TachoBar73.set_src(screen_TachoBar73_img)
screen_TachoBar73.set_pivot(0,0)
screen_TachoBar73.set_angle(0)
# create style style_screen_tachobar73_main_main_default
style_screen_tachobar73_main_main_default = lv.style_t()
style_screen_tachobar73_main_main_default.init()
style_screen_tachobar73_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar73_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar73_main_main_default.set_img_opa(0)

# add style for screen_TachoBar73
screen_TachoBar73.add_style(style_screen_tachobar73_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar74 = lv.img(screen)
screen_TachoBar74.set_pos(3,8)
screen_TachoBar74.set_size(231,78)
screen_TachoBar74.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-179760368.png','rb') as f:
        screen_TachoBar74_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-179760368.png')
    sys.exit()

screen_TachoBar74_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar74_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar74_img_data
})

screen_TachoBar74.set_src(screen_TachoBar74_img)
screen_TachoBar74.set_pivot(0,0)
screen_TachoBar74.set_angle(0)
# create style style_screen_tachobar74_main_main_default
style_screen_tachobar74_main_main_default = lv.style_t()
style_screen_tachobar74_main_main_default.init()
style_screen_tachobar74_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar74_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar74_main_main_default.set_img_opa(0)

# add style for screen_TachoBar74
screen_TachoBar74.add_style(style_screen_tachobar74_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar75 = lv.img(screen)
screen_TachoBar75.set_pos(3,8)
screen_TachoBar75.set_size(231,78)
screen_TachoBar75.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-148740561.png','rb') as f:
        screen_TachoBar75_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-148740561.png')
    sys.exit()

screen_TachoBar75_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar75_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar75_img_data
})

screen_TachoBar75.set_src(screen_TachoBar75_img)
screen_TachoBar75.set_pivot(0,0)
screen_TachoBar75.set_angle(0)
# create style style_screen_tachobar75_main_main_default
style_screen_tachobar75_main_main_default = lv.style_t()
style_screen_tachobar75_main_main_default.init()
style_screen_tachobar75_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar75_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar75_main_main_default.set_img_opa(0)

# add style for screen_TachoBar75
screen_TachoBar75.add_style(style_screen_tachobar75_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar76 = lv.img(screen)
screen_TachoBar76.set_pos(3,8)
screen_TachoBar76.set_size(231,78)
screen_TachoBar76.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-747246930.png','rb') as f:
        screen_TachoBar76_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-747246930.png')
    sys.exit()

screen_TachoBar76_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar76_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar76_img_data
})

screen_TachoBar76.set_src(screen_TachoBar76_img)
screen_TachoBar76.set_pivot(0,0)
screen_TachoBar76.set_angle(0)
# create style style_screen_tachobar76_main_main_default
style_screen_tachobar76_main_main_default = lv.style_t()
style_screen_tachobar76_main_main_default.init()
style_screen_tachobar76_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar76_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar76_main_main_default.set_img_opa(0)

# add style for screen_TachoBar76
screen_TachoBar76.add_style(style_screen_tachobar76_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar77 = lv.img(screen)
screen_TachoBar77.set_pos(3,8)
screen_TachoBar77.set_size(231,78)
screen_TachoBar77.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-716227123.png','rb') as f:
        screen_TachoBar77_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-716227123.png')
    sys.exit()

screen_TachoBar77_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar77_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar77_img_data
})

screen_TachoBar77.set_src(screen_TachoBar77_img)
screen_TachoBar77.set_pivot(0,0)
screen_TachoBar77.set_angle(0)
# create style style_screen_tachobar77_main_main_default
style_screen_tachobar77_main_main_default = lv.style_t()
style_screen_tachobar77_main_main_default.init()
style_screen_tachobar77_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar77_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar77_main_main_default.set_img_opa(0)

# add style for screen_TachoBar77
screen_TachoBar77.add_style(style_screen_tachobar77_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar78 = lv.img(screen)
screen_TachoBar78.set_pos(3,8)
screen_TachoBar78.set_size(231,78)
screen_TachoBar78.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-685207316.png','rb') as f:
        screen_TachoBar78_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-685207316.png')
    sys.exit()

screen_TachoBar78_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar78_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar78_img_data
})

screen_TachoBar78.set_src(screen_TachoBar78_img)
screen_TachoBar78.set_pivot(0,0)
screen_TachoBar78.set_angle(0)
# create style style_screen_tachobar78_main_main_default
style_screen_tachobar78_main_main_default = lv.style_t()
style_screen_tachobar78_main_main_default.init()
style_screen_tachobar78_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar78_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar78_main_main_default.set_img_opa(0)

# add style for screen_TachoBar78
screen_TachoBar78.add_style(style_screen_tachobar78_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar79 = lv.img(screen)
screen_TachoBar79.set_pos(3,8)
screen_TachoBar79.set_size(231,78)
screen_TachoBar79.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-654187509.png','rb') as f:
        screen_TachoBar79_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-654187509.png')
    sys.exit()

screen_TachoBar79_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar79_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar79_img_data
})

screen_TachoBar79.set_src(screen_TachoBar79_img)
screen_TachoBar79.set_pivot(0,0)
screen_TachoBar79.set_angle(0)
# create style style_screen_tachobar79_main_main_default
style_screen_tachobar79_main_main_default = lv.style_t()
style_screen_tachobar79_main_main_default.init()
style_screen_tachobar79_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar79_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar79_main_main_default.set_img_opa(0)

# add style for screen_TachoBar79
screen_TachoBar79.add_style(style_screen_tachobar79_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar80 = lv.img(screen)
screen_TachoBar80.set_pos(3,8)
screen_TachoBar80.set_size(231,78)
screen_TachoBar80.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-623167702.png','rb') as f:
        screen_TachoBar80_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-623167702.png')
    sys.exit()

screen_TachoBar80_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar80_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar80_img_data
})

screen_TachoBar80.set_src(screen_TachoBar80_img)
screen_TachoBar80.set_pivot(0,0)
screen_TachoBar80.set_angle(0)
# create style style_screen_tachobar80_main_main_default
style_screen_tachobar80_main_main_default = lv.style_t()
style_screen_tachobar80_main_main_default.init()
style_screen_tachobar80_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar80_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar80_main_main_default.set_img_opa(0)

# add style for screen_TachoBar80
screen_TachoBar80.add_style(style_screen_tachobar80_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar81 = lv.img(screen)
screen_TachoBar81.set_pos(3,8)
screen_TachoBar81.set_size(231,78)
screen_TachoBar81.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-592147895.png','rb') as f:
        screen_TachoBar81_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-592147895.png')
    sys.exit()

screen_TachoBar81_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar81_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar81_img_data
})

screen_TachoBar81.set_src(screen_TachoBar81_img)
screen_TachoBar81.set_pivot(0,0)
screen_TachoBar81.set_angle(0)
# create style style_screen_tachobar81_main_main_default
style_screen_tachobar81_main_main_default = lv.style_t()
style_screen_tachobar81_main_main_default.init()
style_screen_tachobar81_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar81_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar81_main_main_default.set_img_opa(0)

# add style for screen_TachoBar81
screen_TachoBar81.add_style(style_screen_tachobar81_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar82 = lv.img(screen)
screen_TachoBar82.set_pos(3,8)
screen_TachoBar82.set_size(231,78)
screen_TachoBar82.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-561128088.png','rb') as f:
        screen_TachoBar82_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-561128088.png')
    sys.exit()

screen_TachoBar82_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar82_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar82_img_data
})

screen_TachoBar82.set_src(screen_TachoBar82_img)
screen_TachoBar82.set_pivot(0,0)
screen_TachoBar82.set_angle(0)
# create style style_screen_tachobar82_main_main_default
style_screen_tachobar82_main_main_default = lv.style_t()
style_screen_tachobar82_main_main_default.init()
style_screen_tachobar82_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar82_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar82_main_main_default.set_img_opa(0)

# add style for screen_TachoBar82
screen_TachoBar82.add_style(style_screen_tachobar82_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar83 = lv.img(screen)
screen_TachoBar83.set_pos(3,8)
screen_TachoBar83.set_size(231,78)
screen_TachoBar83.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-530108281.png','rb') as f:
        screen_TachoBar83_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-530108281.png')
    sys.exit()

screen_TachoBar83_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar83_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar83_img_data
})

screen_TachoBar83.set_src(screen_TachoBar83_img)
screen_TachoBar83.set_pivot(0,0)
screen_TachoBar83.set_angle(0)
# create style style_screen_tachobar83_main_main_default
style_screen_tachobar83_main_main_default = lv.style_t()
style_screen_tachobar83_main_main_default.init()
style_screen_tachobar83_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar83_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar83_main_main_default.set_img_opa(0)

# add style for screen_TachoBar83
screen_TachoBar83.add_style(style_screen_tachobar83_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar84 = lv.img(screen)
screen_TachoBar84.set_pos(3,8)
screen_TachoBar84.set_size(231,78)
screen_TachoBar84.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-499088474.png','rb') as f:
        screen_TachoBar84_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-499088474.png')
    sys.exit()

screen_TachoBar84_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar84_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar84_img_data
})

screen_TachoBar84.set_src(screen_TachoBar84_img)
screen_TachoBar84.set_pivot(0,0)
screen_TachoBar84.set_angle(0)
# create style style_screen_tachobar84_main_main_default
style_screen_tachobar84_main_main_default = lv.style_t()
style_screen_tachobar84_main_main_default.init()
style_screen_tachobar84_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar84_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar84_main_main_default.set_img_opa(0)

# add style for screen_TachoBar84
screen_TachoBar84.add_style(style_screen_tachobar84_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar85 = lv.img(screen)
screen_TachoBar85.set_pos(3,8)
screen_TachoBar85.set_size(231,78)
screen_TachoBar85.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-468068667.png','rb') as f:
        screen_TachoBar85_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-468068667.png')
    sys.exit()

screen_TachoBar85_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar85_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar85_img_data
})

screen_TachoBar85.set_src(screen_TachoBar85_img)
screen_TachoBar85.set_pivot(0,0)
screen_TachoBar85.set_angle(0)
# create style style_screen_tachobar85_main_main_default
style_screen_tachobar85_main_main_default = lv.style_t()
style_screen_tachobar85_main_main_default.init()
style_screen_tachobar85_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar85_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar85_main_main_default.set_img_opa(0)

# add style for screen_TachoBar85
screen_TachoBar85.add_style(style_screen_tachobar85_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar86 = lv.img(screen)
screen_TachoBar86.set_pos(3,8)
screen_TachoBar86.set_size(231,78)
screen_TachoBar86.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp214367087.png','rb') as f:
        screen_TachoBar86_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp214367087.png')
    sys.exit()

screen_TachoBar86_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar86_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar86_img_data
})

screen_TachoBar86.set_src(screen_TachoBar86_img)
screen_TachoBar86.set_pivot(0,0)
screen_TachoBar86.set_angle(0)
# create style style_screen_tachobar86_main_main_default
style_screen_tachobar86_main_main_default = lv.style_t()
style_screen_tachobar86_main_main_default.init()
style_screen_tachobar86_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar86_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar86_main_main_default.set_img_opa(0)

# add style for screen_TachoBar86
screen_TachoBar86.add_style(style_screen_tachobar86_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar87 = lv.img(screen)
screen_TachoBar87.set_pos(3,8)
screen_TachoBar87.set_size(231,78)
screen_TachoBar87.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp245386894.png','rb') as f:
        screen_TachoBar87_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp245386894.png')
    sys.exit()

screen_TachoBar87_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar87_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar87_img_data
})

screen_TachoBar87.set_src(screen_TachoBar87_img)
screen_TachoBar87.set_pivot(0,0)
screen_TachoBar87.set_angle(0)
# create style style_screen_tachobar87_main_main_default
style_screen_tachobar87_main_main_default = lv.style_t()
style_screen_tachobar87_main_main_default.init()
style_screen_tachobar87_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar87_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar87_main_main_default.set_img_opa(0)

# add style for screen_TachoBar87
screen_TachoBar87.add_style(style_screen_tachobar87_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar88 = lv.img(screen)
screen_TachoBar88.set_pos(3,8)
screen_TachoBar88.set_size(231,78)
screen_TachoBar88.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp276406701.png','rb') as f:
        screen_TachoBar88_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp276406701.png')
    sys.exit()

screen_TachoBar88_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar88_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar88_img_data
})

screen_TachoBar88.set_src(screen_TachoBar88_img)
screen_TachoBar88.set_pivot(0,0)
screen_TachoBar88.set_angle(0)
# create style style_screen_tachobar88_main_main_default
style_screen_tachobar88_main_main_default = lv.style_t()
style_screen_tachobar88_main_main_default.init()
style_screen_tachobar88_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar88_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar88_main_main_default.set_img_opa(0)

# add style for screen_TachoBar88
screen_TachoBar88.add_style(style_screen_tachobar88_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar89 = lv.img(screen)
screen_TachoBar89.set_pos(3,8)
screen_TachoBar89.set_size(231,78)
screen_TachoBar89.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp307426508.png','rb') as f:
        screen_TachoBar89_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp307426508.png')
    sys.exit()

screen_TachoBar89_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar89_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar89_img_data
})

screen_TachoBar89.set_src(screen_TachoBar89_img)
screen_TachoBar89.set_pivot(0,0)
screen_TachoBar89.set_angle(0)
# create style style_screen_tachobar89_main_main_default
style_screen_tachobar89_main_main_default = lv.style_t()
style_screen_tachobar89_main_main_default.init()
style_screen_tachobar89_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar89_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar89_main_main_default.set_img_opa(0)

# add style for screen_TachoBar89
screen_TachoBar89.add_style(style_screen_tachobar89_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar90 = lv.img(screen)
screen_TachoBar90.set_pos(3,8)
screen_TachoBar90.set_size(231,78)
screen_TachoBar90.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp338446315.png','rb') as f:
        screen_TachoBar90_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp338446315.png')
    sys.exit()

screen_TachoBar90_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar90_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar90_img_data
})

screen_TachoBar90.set_src(screen_TachoBar90_img)
screen_TachoBar90.set_pivot(0,0)
screen_TachoBar90.set_angle(0)
# create style style_screen_tachobar90_main_main_default
style_screen_tachobar90_main_main_default = lv.style_t()
style_screen_tachobar90_main_main_default.init()
style_screen_tachobar90_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar90_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar90_main_main_default.set_img_opa(0)

# add style for screen_TachoBar90
screen_TachoBar90.add_style(style_screen_tachobar90_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar91 = lv.img(screen)
screen_TachoBar91.set_pos(3,8)
screen_TachoBar91.set_size(231,78)
screen_TachoBar91.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp369466122.png','rb') as f:
        screen_TachoBar91_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp369466122.png')
    sys.exit()

screen_TachoBar91_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar91_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar91_img_data
})

screen_TachoBar91.set_src(screen_TachoBar91_img)
screen_TachoBar91.set_pivot(0,0)
screen_TachoBar91.set_angle(0)
# create style style_screen_tachobar91_main_main_default
style_screen_tachobar91_main_main_default = lv.style_t()
style_screen_tachobar91_main_main_default.init()
style_screen_tachobar91_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar91_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar91_main_main_default.set_img_opa(0)

# add style for screen_TachoBar91
screen_TachoBar91.add_style(style_screen_tachobar91_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar92 = lv.img(screen)
screen_TachoBar92.set_pos(3,8)
screen_TachoBar92.set_size(231,78)
screen_TachoBar92.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp400485929.png','rb') as f:
        screen_TachoBar92_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp400485929.png')
    sys.exit()

screen_TachoBar92_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar92_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar92_img_data
})

screen_TachoBar92.set_src(screen_TachoBar92_img)
screen_TachoBar92.set_pivot(0,0)
screen_TachoBar92.set_angle(0)
# create style style_screen_tachobar92_main_main_default
style_screen_tachobar92_main_main_default = lv.style_t()
style_screen_tachobar92_main_main_default.init()
style_screen_tachobar92_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar92_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar92_main_main_default.set_img_opa(0)

# add style for screen_TachoBar92
screen_TachoBar92.add_style(style_screen_tachobar92_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar93 = lv.img(screen)
screen_TachoBar93.set_pos(3,8)
screen_TachoBar93.set_size(231,78)
screen_TachoBar93.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp431505736.png','rb') as f:
        screen_TachoBar93_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp431505736.png')
    sys.exit()

screen_TachoBar93_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar93_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar93_img_data
})

screen_TachoBar93.set_src(screen_TachoBar93_img)
screen_TachoBar93.set_pivot(0,0)
screen_TachoBar93.set_angle(0)
# create style style_screen_tachobar93_main_main_default
style_screen_tachobar93_main_main_default = lv.style_t()
style_screen_tachobar93_main_main_default.init()
style_screen_tachobar93_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar93_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar93_main_main_default.set_img_opa(0)

# add style for screen_TachoBar93
screen_TachoBar93.add_style(style_screen_tachobar93_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar94 = lv.img(screen)
screen_TachoBar94.set_pos(3,8)
screen_TachoBar94.set_size(231,78)
screen_TachoBar94.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp462525543.png','rb') as f:
        screen_TachoBar94_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp462525543.png')
    sys.exit()

screen_TachoBar94_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar94_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar94_img_data
})

screen_TachoBar94.set_src(screen_TachoBar94_img)
screen_TachoBar94.set_pivot(0,0)
screen_TachoBar94.set_angle(0)
# create style style_screen_tachobar94_main_main_default
style_screen_tachobar94_main_main_default = lv.style_t()
style_screen_tachobar94_main_main_default.init()
style_screen_tachobar94_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar94_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar94_main_main_default.set_img_opa(0)

# add style for screen_TachoBar94
screen_TachoBar94.add_style(style_screen_tachobar94_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar95 = lv.img(screen)
screen_TachoBar95.set_pos(3,8)
screen_TachoBar95.set_size(231,78)
screen_TachoBar95.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp493545350.png','rb') as f:
        screen_TachoBar95_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp493545350.png')
    sys.exit()

screen_TachoBar95_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar95_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar95_img_data
})

screen_TachoBar95.set_src(screen_TachoBar95_img)
screen_TachoBar95.set_pivot(0,0)
screen_TachoBar95.set_angle(0)
# create style style_screen_tachobar95_main_main_default
style_screen_tachobar95_main_main_default = lv.style_t()
style_screen_tachobar95_main_main_default.init()
style_screen_tachobar95_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar95_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar95_main_main_default.set_img_opa(0)

# add style for screen_TachoBar95
screen_TachoBar95.add_style(style_screen_tachobar95_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar96 = lv.img(screen)
screen_TachoBar96.set_pos(3,8)
screen_TachoBar96.set_size(231,78)
screen_TachoBar96.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp1175981104.png','rb') as f:
        screen_TachoBar96_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp1175981104.png')
    sys.exit()

screen_TachoBar96_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar96_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar96_img_data
})

screen_TachoBar96.set_src(screen_TachoBar96_img)
screen_TachoBar96.set_pivot(0,0)
screen_TachoBar96.set_angle(0)
# create style style_screen_tachobar96_main_main_default
style_screen_tachobar96_main_main_default = lv.style_t()
style_screen_tachobar96_main_main_default.init()
style_screen_tachobar96_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar96_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar96_main_main_default.set_img_opa(0)

# add style for screen_TachoBar96
screen_TachoBar96.add_style(style_screen_tachobar96_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar97 = lv.img(screen)
screen_TachoBar97.set_pos(3,8)
screen_TachoBar97.set_size(231,78)
screen_TachoBar97.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp1207000911.png','rb') as f:
        screen_TachoBar97_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp1207000911.png')
    sys.exit()

screen_TachoBar97_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar97_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar97_img_data
})

screen_TachoBar97.set_src(screen_TachoBar97_img)
screen_TachoBar97.set_pivot(0,0)
screen_TachoBar97.set_angle(0)
# create style style_screen_tachobar97_main_main_default
style_screen_tachobar97_main_main_default = lv.style_t()
style_screen_tachobar97_main_main_default.init()
style_screen_tachobar97_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar97_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar97_main_main_default.set_img_opa(0)

# add style for screen_TachoBar97
screen_TachoBar97.add_style(style_screen_tachobar97_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar98 = lv.img(screen)
screen_TachoBar98.set_pos(3,8)
screen_TachoBar98.set_size(231,78)
screen_TachoBar98.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp1238020718.png','rb') as f:
        screen_TachoBar98_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp1238020718.png')
    sys.exit()

screen_TachoBar98_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar98_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar98_img_data
})

screen_TachoBar98.set_src(screen_TachoBar98_img)
screen_TachoBar98.set_pivot(0,0)
screen_TachoBar98.set_angle(0)
# create style style_screen_tachobar98_main_main_default
style_screen_tachobar98_main_main_default = lv.style_t()
style_screen_tachobar98_main_main_default.init()
style_screen_tachobar98_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar98_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar98_main_main_default.set_img_opa(0)

# add style for screen_TachoBar98
screen_TachoBar98.add_style(style_screen_tachobar98_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar99 = lv.img(screen)
screen_TachoBar99.set_pos(3,8)
screen_TachoBar99.set_size(231,78)
screen_TachoBar99.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp1269040525.png','rb') as f:
        screen_TachoBar99_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp1269040525.png')
    sys.exit()

screen_TachoBar99_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar99_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar99_img_data
})

screen_TachoBar99.set_src(screen_TachoBar99_img)
screen_TachoBar99.set_pivot(0,0)
screen_TachoBar99.set_angle(0)
# create style style_screen_tachobar99_main_main_default
style_screen_tachobar99_main_main_default = lv.style_t()
style_screen_tachobar99_main_main_default.init()
style_screen_tachobar99_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar99_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar99_main_main_default.set_img_opa(0)

# add style for screen_TachoBar99
screen_TachoBar99.add_style(style_screen_tachobar99_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar100 = lv.img(screen)
screen_TachoBar100.set_pos(3,8)
screen_TachoBar100.set_size(231,78)
screen_TachoBar100.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp1300060332.png','rb') as f:
        screen_TachoBar100_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp1300060332.png')
    sys.exit()

screen_TachoBar100_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar100_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar100_img_data
})

screen_TachoBar100.set_src(screen_TachoBar100_img)
screen_TachoBar100.set_pivot(0,0)
screen_TachoBar100.set_angle(0)
# create style style_screen_tachobar100_main_main_default
style_screen_tachobar100_main_main_default = lv.style_t()
style_screen_tachobar100_main_main_default.init()
style_screen_tachobar100_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar100_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar100_main_main_default.set_img_opa(0)

# add style for screen_TachoBar100
screen_TachoBar100.add_style(style_screen_tachobar100_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar101 = lv.img(screen)
screen_TachoBar101.set_pos(3,8)
screen_TachoBar101.set_size(231,78)
screen_TachoBar101.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp1331080139.png','rb') as f:
        screen_TachoBar101_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp1331080139.png')
    sys.exit()

screen_TachoBar101_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar101_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar101_img_data
})

screen_TachoBar101.set_src(screen_TachoBar101_img)
screen_TachoBar101.set_pivot(0,0)
screen_TachoBar101.set_angle(0)
# create style style_screen_tachobar101_main_main_default
style_screen_tachobar101_main_main_default = lv.style_t()
style_screen_tachobar101_main_main_default.init()
style_screen_tachobar101_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar101_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar101_main_main_default.set_img_opa(0)

# add style for screen_TachoBar101
screen_TachoBar101.add_style(style_screen_tachobar101_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar102 = lv.img(screen)
screen_TachoBar102.set_pos(3,8)
screen_TachoBar102.set_size(231,78)
screen_TachoBar102.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp1362099946.png','rb') as f:
        screen_TachoBar102_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp1362099946.png')
    sys.exit()

screen_TachoBar102_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar102_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar102_img_data
})

screen_TachoBar102.set_src(screen_TachoBar102_img)
screen_TachoBar102.set_pivot(0,0)
screen_TachoBar102.set_angle(0)
# create style style_screen_tachobar102_main_main_default
style_screen_tachobar102_main_main_default = lv.style_t()
style_screen_tachobar102_main_main_default.init()
style_screen_tachobar102_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar102_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar102_main_main_default.set_img_opa(0)

# add style for screen_TachoBar102
screen_TachoBar102.add_style(style_screen_tachobar102_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar103 = lv.img(screen)
screen_TachoBar103.set_pos(3,8)
screen_TachoBar103.set_size(231,78)
screen_TachoBar103.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp1393119753.png','rb') as f:
        screen_TachoBar103_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp1393119753.png')
    sys.exit()

screen_TachoBar103_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar103_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar103_img_data
})

screen_TachoBar103.set_src(screen_TachoBar103_img)
screen_TachoBar103.set_pivot(0,0)
screen_TachoBar103.set_angle(0)
# create style style_screen_tachobar103_main_main_default
style_screen_tachobar103_main_main_default = lv.style_t()
style_screen_tachobar103_main_main_default.init()
style_screen_tachobar103_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar103_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar103_main_main_default.set_img_opa(0)

# add style for screen_TachoBar103
screen_TachoBar103.add_style(style_screen_tachobar103_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar104 = lv.img(screen)
screen_TachoBar104.set_pos(3,8)
screen_TachoBar104.set_size(231,78)
screen_TachoBar104.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp1424139560.png','rb') as f:
        screen_TachoBar104_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp1424139560.png')
    sys.exit()

screen_TachoBar104_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar104_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar104_img_data
})

screen_TachoBar104.set_src(screen_TachoBar104_img)
screen_TachoBar104.set_pivot(0,0)
screen_TachoBar104.set_angle(0)
# create style style_screen_tachobar104_main_main_default
style_screen_tachobar104_main_main_default = lv.style_t()
style_screen_tachobar104_main_main_default.init()
style_screen_tachobar104_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar104_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar104_main_main_default.set_img_opa(0)

# add style for screen_TachoBar104
screen_TachoBar104.add_style(style_screen_tachobar104_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar105 = lv.img(screen)
screen_TachoBar105.set_pos(3,8)
screen_TachoBar105.set_size(231,78)
screen_TachoBar105.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp1455159367.png','rb') as f:
        screen_TachoBar105_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp1455159367.png')
    sys.exit()

screen_TachoBar105_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar105_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar105_img_data
})

screen_TachoBar105.set_src(screen_TachoBar105_img)
screen_TachoBar105.set_pivot(0,0)
screen_TachoBar105.set_angle(0)
# create style style_screen_tachobar105_main_main_default
style_screen_tachobar105_main_main_default = lv.style_t()
style_screen_tachobar105_main_main_default.init()
style_screen_tachobar105_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar105_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar105_main_main_default.set_img_opa(0)

# add style for screen_TachoBar105
screen_TachoBar105.add_style(style_screen_tachobar105_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar106 = lv.img(screen)
screen_TachoBar106.set_pos(3,8)
screen_TachoBar106.set_size(231,78)
screen_TachoBar106.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp2137595121.png','rb') as f:
        screen_TachoBar106_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp2137595121.png')
    sys.exit()

screen_TachoBar106_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar106_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar106_img_data
})

screen_TachoBar106.set_src(screen_TachoBar106_img)
screen_TachoBar106.set_pivot(0,0)
screen_TachoBar106.set_angle(0)
# create style style_screen_tachobar106_main_main_default
style_screen_tachobar106_main_main_default = lv.style_t()
style_screen_tachobar106_main_main_default.init()
style_screen_tachobar106_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar106_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar106_main_main_default.set_img_opa(0)

# add style for screen_TachoBar106
screen_TachoBar106.add_style(style_screen_tachobar106_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar107 = lv.img(screen)
screen_TachoBar107.set_pos(3,8)
screen_TachoBar107.set_size(231,78)
screen_TachoBar107.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-2126352368.png','rb') as f:
        screen_TachoBar107_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-2126352368.png')
    sys.exit()

screen_TachoBar107_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar107_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar107_img_data
})

screen_TachoBar107.set_src(screen_TachoBar107_img)
screen_TachoBar107.set_pivot(0,0)
screen_TachoBar107.set_angle(0)
# create style style_screen_tachobar107_main_main_default
style_screen_tachobar107_main_main_default = lv.style_t()
style_screen_tachobar107_main_main_default.init()
style_screen_tachobar107_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar107_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar107_main_main_default.set_img_opa(0)

# add style for screen_TachoBar107
screen_TachoBar107.add_style(style_screen_tachobar107_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar108 = lv.img(screen)
screen_TachoBar108.set_pos(3,8)
screen_TachoBar108.set_size(231,78)
screen_TachoBar108.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-2095332561.png','rb') as f:
        screen_TachoBar108_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-2095332561.png')
    sys.exit()

screen_TachoBar108_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar108_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar108_img_data
})

screen_TachoBar108.set_src(screen_TachoBar108_img)
screen_TachoBar108.set_pivot(0,0)
screen_TachoBar108.set_angle(0)
# create style style_screen_tachobar108_main_main_default
style_screen_tachobar108_main_main_default = lv.style_t()
style_screen_tachobar108_main_main_default.init()
style_screen_tachobar108_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar108_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar108_main_main_default.set_img_opa(0)

# add style for screen_TachoBar108
screen_TachoBar108.add_style(style_screen_tachobar108_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar109 = lv.img(screen)
screen_TachoBar109.set_pos(3,8)
screen_TachoBar109.set_size(231,78)
screen_TachoBar109.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-2064312754.png','rb') as f:
        screen_TachoBar109_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-2064312754.png')
    sys.exit()

screen_TachoBar109_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar109_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar109_img_data
})

screen_TachoBar109.set_src(screen_TachoBar109_img)
screen_TachoBar109.set_pivot(0,0)
screen_TachoBar109.set_angle(0)
# create style style_screen_tachobar109_main_main_default
style_screen_tachobar109_main_main_default = lv.style_t()
style_screen_tachobar109_main_main_default.init()
style_screen_tachobar109_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar109_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar109_main_main_default.set_img_opa(0)

# add style for screen_TachoBar109
screen_TachoBar109.add_style(style_screen_tachobar109_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar110 = lv.img(screen)
screen_TachoBar110.set_pos(3,8)
screen_TachoBar110.set_size(231,78)
screen_TachoBar110.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-2033292947.png','rb') as f:
        screen_TachoBar110_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-2033292947.png')
    sys.exit()

screen_TachoBar110_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar110_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar110_img_data
})

screen_TachoBar110.set_src(screen_TachoBar110_img)
screen_TachoBar110.set_pivot(0,0)
screen_TachoBar110.set_angle(0)
# create style style_screen_tachobar110_main_main_default
style_screen_tachobar110_main_main_default = lv.style_t()
style_screen_tachobar110_main_main_default.init()
style_screen_tachobar110_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar110_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar110_main_main_default.set_img_opa(0)

# add style for screen_TachoBar110
screen_TachoBar110.add_style(style_screen_tachobar110_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar111 = lv.img(screen)
screen_TachoBar111.set_pos(3,8)
screen_TachoBar111.set_size(231,78)
screen_TachoBar111.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-2002273140.png','rb') as f:
        screen_TachoBar111_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-2002273140.png')
    sys.exit()

screen_TachoBar111_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar111_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar111_img_data
})

screen_TachoBar111.set_src(screen_TachoBar111_img)
screen_TachoBar111.set_pivot(0,0)
screen_TachoBar111.set_angle(0)
# create style style_screen_tachobar111_main_main_default
style_screen_tachobar111_main_main_default = lv.style_t()
style_screen_tachobar111_main_main_default.init()
style_screen_tachobar111_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar111_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar111_main_main_default.set_img_opa(0)

# add style for screen_TachoBar111
screen_TachoBar111.add_style(style_screen_tachobar111_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar112 = lv.img(screen)
screen_TachoBar112.set_pos(3,8)
screen_TachoBar112.set_size(231,78)
screen_TachoBar112.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1971253333.png','rb') as f:
        screen_TachoBar112_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1971253333.png')
    sys.exit()

screen_TachoBar112_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar112_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar112_img_data
})

screen_TachoBar112.set_src(screen_TachoBar112_img)
screen_TachoBar112.set_pivot(0,0)
screen_TachoBar112.set_angle(0)
# create style style_screen_tachobar112_main_main_default
style_screen_tachobar112_main_main_default = lv.style_t()
style_screen_tachobar112_main_main_default.init()
style_screen_tachobar112_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar112_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar112_main_main_default.set_img_opa(0)

# add style for screen_TachoBar112
screen_TachoBar112.add_style(style_screen_tachobar112_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar113 = lv.img(screen)
screen_TachoBar113.set_pos(3,8)
screen_TachoBar113.set_size(231,78)
screen_TachoBar113.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1940233526.png','rb') as f:
        screen_TachoBar113_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1940233526.png')
    sys.exit()

screen_TachoBar113_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar113_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar113_img_data
})

screen_TachoBar113.set_src(screen_TachoBar113_img)
screen_TachoBar113.set_pivot(0,0)
screen_TachoBar113.set_angle(0)
# create style style_screen_tachobar113_main_main_default
style_screen_tachobar113_main_main_default = lv.style_t()
style_screen_tachobar113_main_main_default.init()
style_screen_tachobar113_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar113_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar113_main_main_default.set_img_opa(0)

# add style for screen_TachoBar113
screen_TachoBar113.add_style(style_screen_tachobar113_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar114 = lv.img(screen)
screen_TachoBar114.set_pos(3,8)
screen_TachoBar114.set_size(231,78)
screen_TachoBar114.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1909213719.png','rb') as f:
        screen_TachoBar114_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1909213719.png')
    sys.exit()

screen_TachoBar114_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar114_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar114_img_data
})

screen_TachoBar114.set_src(screen_TachoBar114_img)
screen_TachoBar114.set_pivot(0,0)
screen_TachoBar114.set_angle(0)
# create style style_screen_tachobar114_main_main_default
style_screen_tachobar114_main_main_default = lv.style_t()
style_screen_tachobar114_main_main_default.init()
style_screen_tachobar114_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar114_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar114_main_main_default.set_img_opa(0)

# add style for screen_TachoBar114
screen_TachoBar114.add_style(style_screen_tachobar114_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar115 = lv.img(screen)
screen_TachoBar115.set_pos(3,8)
screen_TachoBar115.set_size(231,78)
screen_TachoBar115.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1878193912.png','rb') as f:
        screen_TachoBar115_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1878193912.png')
    sys.exit()

screen_TachoBar115_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar115_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar115_img_data
})

screen_TachoBar115.set_src(screen_TachoBar115_img)
screen_TachoBar115.set_pivot(0,0)
screen_TachoBar115.set_angle(0)
# create style style_screen_tachobar115_main_main_default
style_screen_tachobar115_main_main_default = lv.style_t()
style_screen_tachobar115_main_main_default.init()
style_screen_tachobar115_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar115_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar115_main_main_default.set_img_opa(0)

# add style for screen_TachoBar115
screen_TachoBar115.add_style(style_screen_tachobar115_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar116 = lv.img(screen)
screen_TachoBar116.set_pos(3,8)
screen_TachoBar116.set_size(231,78)
screen_TachoBar116.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1195758158.png','rb') as f:
        screen_TachoBar116_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1195758158.png')
    sys.exit()

screen_TachoBar116_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar116_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar116_img_data
})

screen_TachoBar116.set_src(screen_TachoBar116_img)
screen_TachoBar116.set_pivot(0,0)
screen_TachoBar116.set_angle(0)
# create style style_screen_tachobar116_main_main_default
style_screen_tachobar116_main_main_default = lv.style_t()
style_screen_tachobar116_main_main_default.init()
style_screen_tachobar116_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar116_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar116_main_main_default.set_img_opa(0)

# add style for screen_TachoBar116
screen_TachoBar116.add_style(style_screen_tachobar116_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar117 = lv.img(screen)
screen_TachoBar117.set_pos(3,8)
screen_TachoBar117.set_size(231,78)
screen_TachoBar117.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1164738351.png','rb') as f:
        screen_TachoBar117_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1164738351.png')
    sys.exit()

screen_TachoBar117_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar117_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar117_img_data
})

screen_TachoBar117.set_src(screen_TachoBar117_img)
screen_TachoBar117.set_pivot(0,0)
screen_TachoBar117.set_angle(0)
# create style style_screen_tachobar117_main_main_default
style_screen_tachobar117_main_main_default = lv.style_t()
style_screen_tachobar117_main_main_default.init()
style_screen_tachobar117_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar117_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar117_main_main_default.set_img_opa(0)

# add style for screen_TachoBar117
screen_TachoBar117.add_style(style_screen_tachobar117_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar118 = lv.img(screen)
screen_TachoBar118.set_pos(3,8)
screen_TachoBar118.set_size(231,78)
screen_TachoBar118.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1133718544.png','rb') as f:
        screen_TachoBar118_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1133718544.png')
    sys.exit()

screen_TachoBar118_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar118_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar118_img_data
})

screen_TachoBar118.set_src(screen_TachoBar118_img)
screen_TachoBar118.set_pivot(0,0)
screen_TachoBar118.set_angle(0)
# create style style_screen_tachobar118_main_main_default
style_screen_tachobar118_main_main_default = lv.style_t()
style_screen_tachobar118_main_main_default.init()
style_screen_tachobar118_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar118_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar118_main_main_default.set_img_opa(0)

# add style for screen_TachoBar118
screen_TachoBar118.add_style(style_screen_tachobar118_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar119 = lv.img(screen)
screen_TachoBar119.set_pos(3,8)
screen_TachoBar119.set_size(231,78)
screen_TachoBar119.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1102698737.png','rb') as f:
        screen_TachoBar119_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1102698737.png')
    sys.exit()

screen_TachoBar119_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar119_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar119_img_data
})

screen_TachoBar119.set_src(screen_TachoBar119_img)
screen_TachoBar119.set_pivot(0,0)
screen_TachoBar119.set_angle(0)
# create style style_screen_tachobar119_main_main_default
style_screen_tachobar119_main_main_default = lv.style_t()
style_screen_tachobar119_main_main_default.init()
style_screen_tachobar119_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar119_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar119_main_main_default.set_img_opa(0)

# add style for screen_TachoBar119
screen_TachoBar119.add_style(style_screen_tachobar119_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar120 = lv.img(screen)
screen_TachoBar120.set_pos(3,8)
screen_TachoBar120.set_size(231,78)
screen_TachoBar120.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1071678930.png','rb') as f:
        screen_TachoBar120_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1071678930.png')
    sys.exit()

screen_TachoBar120_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar120_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar120_img_data
})

screen_TachoBar120.set_src(screen_TachoBar120_img)
screen_TachoBar120.set_pivot(0,0)
screen_TachoBar120.set_angle(0)
# create style style_screen_tachobar120_main_main_default
style_screen_tachobar120_main_main_default = lv.style_t()
style_screen_tachobar120_main_main_default.init()
style_screen_tachobar120_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar120_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar120_main_main_default.set_img_opa(0)

# add style for screen_TachoBar120
screen_TachoBar120.add_style(style_screen_tachobar120_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar121 = lv.img(screen)
screen_TachoBar121.set_pos(3,8)
screen_TachoBar121.set_size(231,78)
screen_TachoBar121.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1040659123.png','rb') as f:
        screen_TachoBar121_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1040659123.png')
    sys.exit()

screen_TachoBar121_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar121_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar121_img_data
})

screen_TachoBar121.set_src(screen_TachoBar121_img)
screen_TachoBar121.set_pivot(0,0)
screen_TachoBar121.set_angle(0)
# create style style_screen_tachobar121_main_main_default
style_screen_tachobar121_main_main_default = lv.style_t()
style_screen_tachobar121_main_main_default.init()
style_screen_tachobar121_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar121_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar121_main_main_default.set_img_opa(0)

# add style for screen_TachoBar121
screen_TachoBar121.add_style(style_screen_tachobar121_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar122 = lv.img(screen)
screen_TachoBar122.set_pos(3,8)
screen_TachoBar122.set_size(231,78)
screen_TachoBar122.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1009639316.png','rb') as f:
        screen_TachoBar122_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1009639316.png')
    sys.exit()

screen_TachoBar122_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar122_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar122_img_data
})

screen_TachoBar122.set_src(screen_TachoBar122_img)
screen_TachoBar122.set_pivot(0,0)
screen_TachoBar122.set_angle(0)
# create style style_screen_tachobar122_main_main_default
style_screen_tachobar122_main_main_default = lv.style_t()
style_screen_tachobar122_main_main_default.init()
style_screen_tachobar122_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar122_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar122_main_main_default.set_img_opa(0)

# add style for screen_TachoBar122
screen_TachoBar122.add_style(style_screen_tachobar122_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar123 = lv.img(screen)
screen_TachoBar123.set_pos(3,8)
screen_TachoBar123.set_size(231,78)
screen_TachoBar123.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-978619509.png','rb') as f:
        screen_TachoBar123_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-978619509.png')
    sys.exit()

screen_TachoBar123_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar123_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar123_img_data
})

screen_TachoBar123.set_src(screen_TachoBar123_img)
screen_TachoBar123.set_pivot(0,0)
screen_TachoBar123.set_angle(0)
# create style style_screen_tachobar123_main_main_default
style_screen_tachobar123_main_main_default = lv.style_t()
style_screen_tachobar123_main_main_default.init()
style_screen_tachobar123_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar123_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar123_main_main_default.set_img_opa(0)

# add style for screen_TachoBar123
screen_TachoBar123.add_style(style_screen_tachobar123_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar124 = lv.img(screen)
screen_TachoBar124.set_pos(3,8)
screen_TachoBar124.set_size(231,78)
screen_TachoBar124.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-947599702.png','rb') as f:
        screen_TachoBar124_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-947599702.png')
    sys.exit()

screen_TachoBar124_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar124_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar124_img_data
})

screen_TachoBar124.set_src(screen_TachoBar124_img)
screen_TachoBar124.set_pivot(0,0)
screen_TachoBar124.set_angle(0)
# create style style_screen_tachobar124_main_main_default
style_screen_tachobar124_main_main_default = lv.style_t()
style_screen_tachobar124_main_main_default.init()
style_screen_tachobar124_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar124_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar124_main_main_default.set_img_opa(0)

# add style for screen_TachoBar124
screen_TachoBar124.add_style(style_screen_tachobar124_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar125 = lv.img(screen)
screen_TachoBar125.set_pos(3,8)
screen_TachoBar125.set_size(231,78)
screen_TachoBar125.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-916579895.png','rb') as f:
        screen_TachoBar125_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-916579895.png')
    sys.exit()

screen_TachoBar125_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar125_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar125_img_data
})

screen_TachoBar125.set_src(screen_TachoBar125_img)
screen_TachoBar125.set_pivot(0,0)
screen_TachoBar125.set_angle(0)
# create style style_screen_tachobar125_main_main_default
style_screen_tachobar125_main_main_default = lv.style_t()
style_screen_tachobar125_main_main_default.init()
style_screen_tachobar125_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar125_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar125_main_main_default.set_img_opa(0)

# add style for screen_TachoBar125
screen_TachoBar125.add_style(style_screen_tachobar125_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar126 = lv.img(screen)
screen_TachoBar126.set_pos(3,8)
screen_TachoBar126.set_size(231,78)
screen_TachoBar126.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-234144141.png','rb') as f:
        screen_TachoBar126_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-234144141.png')
    sys.exit()

screen_TachoBar126_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar126_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar126_img_data
})

screen_TachoBar126.set_src(screen_TachoBar126_img)
screen_TachoBar126.set_pivot(0,0)
screen_TachoBar126.set_angle(0)
# create style style_screen_tachobar126_main_main_default
style_screen_tachobar126_main_main_default = lv.style_t()
style_screen_tachobar126_main_main_default.init()
style_screen_tachobar126_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar126_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar126_main_main_default.set_img_opa(0)

# add style for screen_TachoBar126
screen_TachoBar126.add_style(style_screen_tachobar126_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar127 = lv.img(screen)
screen_TachoBar127.set_pos(3,8)
screen_TachoBar127.set_size(231,78)
screen_TachoBar127.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-203124334.png','rb') as f:
        screen_TachoBar127_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-203124334.png')
    sys.exit()

screen_TachoBar127_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar127_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar127_img_data
})

screen_TachoBar127.set_src(screen_TachoBar127_img)
screen_TachoBar127.set_pivot(0,0)
screen_TachoBar127.set_angle(0)
# create style style_screen_tachobar127_main_main_default
style_screen_tachobar127_main_main_default = lv.style_t()
style_screen_tachobar127_main_main_default.init()
style_screen_tachobar127_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar127_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar127_main_main_default.set_img_opa(0)

# add style for screen_TachoBar127
screen_TachoBar127.add_style(style_screen_tachobar127_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar128 = lv.img(screen)
screen_TachoBar128.set_pos(3,8)
screen_TachoBar128.set_size(231,78)
screen_TachoBar128.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-172104527.png','rb') as f:
        screen_TachoBar128_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-172104527.png')
    sys.exit()

screen_TachoBar128_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar128_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar128_img_data
})

screen_TachoBar128.set_src(screen_TachoBar128_img)
screen_TachoBar128.set_pivot(0,0)
screen_TachoBar128.set_angle(0)
# create style style_screen_tachobar128_main_main_default
style_screen_tachobar128_main_main_default = lv.style_t()
style_screen_tachobar128_main_main_default.init()
style_screen_tachobar128_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar128_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar128_main_main_default.set_img_opa(0)

# add style for screen_TachoBar128
screen_TachoBar128.add_style(style_screen_tachobar128_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar129 = lv.img(screen)
screen_TachoBar129.set_pos(3,8)
screen_TachoBar129.set_size(231,78)
screen_TachoBar129.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-141084720.png','rb') as f:
        screen_TachoBar129_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-141084720.png')
    sys.exit()

screen_TachoBar129_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar129_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar129_img_data
})

screen_TachoBar129.set_src(screen_TachoBar129_img)
screen_TachoBar129.set_pivot(0,0)
screen_TachoBar129.set_angle(0)
# create style style_screen_tachobar129_main_main_default
style_screen_tachobar129_main_main_default = lv.style_t()
style_screen_tachobar129_main_main_default.init()
style_screen_tachobar129_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar129_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar129_main_main_default.set_img_opa(0)

# add style for screen_TachoBar129
screen_TachoBar129.add_style(style_screen_tachobar129_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar130 = lv.img(screen)
screen_TachoBar130.set_pos(3,8)
screen_TachoBar130.set_size(231,78)
screen_TachoBar130.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-110064913.png','rb') as f:
        screen_TachoBar130_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-110064913.png')
    sys.exit()

screen_TachoBar130_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar130_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar130_img_data
})

screen_TachoBar130.set_src(screen_TachoBar130_img)
screen_TachoBar130.set_pivot(0,0)
screen_TachoBar130.set_angle(0)
# create style style_screen_tachobar130_main_main_default
style_screen_tachobar130_main_main_default = lv.style_t()
style_screen_tachobar130_main_main_default.init()
style_screen_tachobar130_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar130_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar130_main_main_default.set_img_opa(0)

# add style for screen_TachoBar130
screen_TachoBar130.add_style(style_screen_tachobar130_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar131 = lv.img(screen)
screen_TachoBar131.set_pos(3,8)
screen_TachoBar131.set_size(231,78)
screen_TachoBar131.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-79045106.png','rb') as f:
        screen_TachoBar131_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-79045106.png')
    sys.exit()

screen_TachoBar131_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar131_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar131_img_data
})

screen_TachoBar131.set_src(screen_TachoBar131_img)
screen_TachoBar131.set_pivot(0,0)
screen_TachoBar131.set_angle(0)
# create style style_screen_tachobar131_main_main_default
style_screen_tachobar131_main_main_default = lv.style_t()
style_screen_tachobar131_main_main_default.init()
style_screen_tachobar131_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar131_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar131_main_main_default.set_img_opa(0)

# add style for screen_TachoBar131
screen_TachoBar131.add_style(style_screen_tachobar131_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar132 = lv.img(screen)
screen_TachoBar132.set_pos(3,8)
screen_TachoBar132.set_size(231,78)
screen_TachoBar132.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-48025299.png','rb') as f:
        screen_TachoBar132_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-48025299.png')
    sys.exit()

screen_TachoBar132_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar132_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar132_img_data
})

screen_TachoBar132.set_src(screen_TachoBar132_img)
screen_TachoBar132.set_pivot(0,0)
screen_TachoBar132.set_angle(0)
# create style style_screen_tachobar132_main_main_default
style_screen_tachobar132_main_main_default = lv.style_t()
style_screen_tachobar132_main_main_default.init()
style_screen_tachobar132_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar132_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar132_main_main_default.set_img_opa(0)

# add style for screen_TachoBar132
screen_TachoBar132.add_style(style_screen_tachobar132_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar133 = lv.img(screen)
screen_TachoBar133.set_pos(3,8)
screen_TachoBar133.set_size(231,78)
screen_TachoBar133.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-17005492.png','rb') as f:
        screen_TachoBar133_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-17005492.png')
    sys.exit()

screen_TachoBar133_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar133_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar133_img_data
})

screen_TachoBar133.set_src(screen_TachoBar133_img)
screen_TachoBar133.set_pivot(0,0)
screen_TachoBar133.set_angle(0)
# create style style_screen_tachobar133_main_main_default
style_screen_tachobar133_main_main_default = lv.style_t()
style_screen_tachobar133_main_main_default.init()
style_screen_tachobar133_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar133_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar133_main_main_default.set_img_opa(0)

# add style for screen_TachoBar133
screen_TachoBar133.add_style(style_screen_tachobar133_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar134 = lv.img(screen)
screen_TachoBar134.set_pos(3,8)
screen_TachoBar134.set_size(231,78)
screen_TachoBar134.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp14014315.png','rb') as f:
        screen_TachoBar134_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp14014315.png')
    sys.exit()

screen_TachoBar134_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar134_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar134_img_data
})

screen_TachoBar134.set_src(screen_TachoBar134_img)
screen_TachoBar134.set_pivot(0,0)
screen_TachoBar134.set_angle(0)
# create style style_screen_tachobar134_main_main_default
style_screen_tachobar134_main_main_default = lv.style_t()
style_screen_tachobar134_main_main_default.init()
style_screen_tachobar134_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar134_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar134_main_main_default.set_img_opa(0)

# add style for screen_TachoBar134
screen_TachoBar134.add_style(style_screen_tachobar134_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar135 = lv.img(screen)
screen_TachoBar135.set_pos(3,8)
screen_TachoBar135.set_size(231,78)
screen_TachoBar135.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp45034122.png','rb') as f:
        screen_TachoBar135_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp45034122.png')
    sys.exit()

screen_TachoBar135_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar135_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar135_img_data
})

screen_TachoBar135.set_src(screen_TachoBar135_img)
screen_TachoBar135.set_pivot(0,0)
screen_TachoBar135.set_angle(0)
# create style style_screen_tachobar135_main_main_default
style_screen_tachobar135_main_main_default = lv.style_t()
style_screen_tachobar135_main_main_default.init()
style_screen_tachobar135_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar135_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar135_main_main_default.set_img_opa(0)

# add style for screen_TachoBar135
screen_TachoBar135.add_style(style_screen_tachobar135_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar136 = lv.img(screen)
screen_TachoBar136.set_pos(3,8)
screen_TachoBar136.set_size(231,78)
screen_TachoBar136.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp727469876.png','rb') as f:
        screen_TachoBar136_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp727469876.png')
    sys.exit()

screen_TachoBar136_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar136_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar136_img_data
})

screen_TachoBar136.set_src(screen_TachoBar136_img)
screen_TachoBar136.set_pivot(0,0)
screen_TachoBar136.set_angle(0)
# create style style_screen_tachobar136_main_main_default
style_screen_tachobar136_main_main_default = lv.style_t()
style_screen_tachobar136_main_main_default.init()
style_screen_tachobar136_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar136_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar136_main_main_default.set_img_opa(0)

# add style for screen_TachoBar136
screen_TachoBar136.add_style(style_screen_tachobar136_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar137 = lv.img(screen)
screen_TachoBar137.set_pos(3,8)
screen_TachoBar137.set_size(231,78)
screen_TachoBar137.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp758489683.png','rb') as f:
        screen_TachoBar137_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp758489683.png')
    sys.exit()

screen_TachoBar137_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar137_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar137_img_data
})

screen_TachoBar137.set_src(screen_TachoBar137_img)
screen_TachoBar137.set_pivot(0,0)
screen_TachoBar137.set_angle(0)
# create style style_screen_tachobar137_main_main_default
style_screen_tachobar137_main_main_default = lv.style_t()
style_screen_tachobar137_main_main_default.init()
style_screen_tachobar137_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar137_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar137_main_main_default.set_img_opa(0)

# add style for screen_TachoBar137
screen_TachoBar137.add_style(style_screen_tachobar137_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar138 = lv.img(screen)
screen_TachoBar138.set_pos(3,8)
screen_TachoBar138.set_size(231,78)
screen_TachoBar138.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp789509490.png','rb') as f:
        screen_TachoBar138_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp789509490.png')
    sys.exit()

screen_TachoBar138_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar138_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar138_img_data
})

screen_TachoBar138.set_src(screen_TachoBar138_img)
screen_TachoBar138.set_pivot(0,0)
screen_TachoBar138.set_angle(0)
# create style style_screen_tachobar138_main_main_default
style_screen_tachobar138_main_main_default = lv.style_t()
style_screen_tachobar138_main_main_default.init()
style_screen_tachobar138_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar138_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar138_main_main_default.set_img_opa(0)

# add style for screen_TachoBar138
screen_TachoBar138.add_style(style_screen_tachobar138_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar139 = lv.img(screen)
screen_TachoBar139.set_pos(3,8)
screen_TachoBar139.set_size(231,78)
screen_TachoBar139.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp820529297.png','rb') as f:
        screen_TachoBar139_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp820529297.png')
    sys.exit()

screen_TachoBar139_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar139_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar139_img_data
})

screen_TachoBar139.set_src(screen_TachoBar139_img)
screen_TachoBar139.set_pivot(0,0)
screen_TachoBar139.set_angle(0)
# create style style_screen_tachobar139_main_main_default
style_screen_tachobar139_main_main_default = lv.style_t()
style_screen_tachobar139_main_main_default.init()
style_screen_tachobar139_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar139_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar139_main_main_default.set_img_opa(0)

# add style for screen_TachoBar139
screen_TachoBar139.add_style(style_screen_tachobar139_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar140 = lv.img(screen)
screen_TachoBar140.set_pos(3,8)
screen_TachoBar140.set_size(231,78)
screen_TachoBar140.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp851549104.png','rb') as f:
        screen_TachoBar140_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp851549104.png')
    sys.exit()

screen_TachoBar140_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar140_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar140_img_data
})

screen_TachoBar140.set_src(screen_TachoBar140_img)
screen_TachoBar140.set_pivot(0,0)
screen_TachoBar140.set_angle(0)
# create style style_screen_tachobar140_main_main_default
style_screen_tachobar140_main_main_default = lv.style_t()
style_screen_tachobar140_main_main_default.init()
style_screen_tachobar140_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar140_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar140_main_main_default.set_img_opa(0)

# add style for screen_TachoBar140
screen_TachoBar140.add_style(style_screen_tachobar140_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar141 = lv.img(screen)
screen_TachoBar141.set_pos(3,8)
screen_TachoBar141.set_size(231,78)
screen_TachoBar141.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp882568911.png','rb') as f:
        screen_TachoBar141_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp882568911.png')
    sys.exit()

screen_TachoBar141_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar141_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar141_img_data
})

screen_TachoBar141.set_src(screen_TachoBar141_img)
screen_TachoBar141.set_pivot(0,0)
screen_TachoBar141.set_angle(0)
# create style style_screen_tachobar141_main_main_default
style_screen_tachobar141_main_main_default = lv.style_t()
style_screen_tachobar141_main_main_default.init()
style_screen_tachobar141_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar141_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar141_main_main_default.set_img_opa(0)

# add style for screen_TachoBar141
screen_TachoBar141.add_style(style_screen_tachobar141_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar142 = lv.img(screen)
screen_TachoBar142.set_pos(3,8)
screen_TachoBar142.set_size(231,78)
screen_TachoBar142.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp913588718.png','rb') as f:
        screen_TachoBar142_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp913588718.png')
    sys.exit()

screen_TachoBar142_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar142_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar142_img_data
})

screen_TachoBar142.set_src(screen_TachoBar142_img)
screen_TachoBar142.set_pivot(0,0)
screen_TachoBar142.set_angle(0)
# create style style_screen_tachobar142_main_main_default
style_screen_tachobar142_main_main_default = lv.style_t()
style_screen_tachobar142_main_main_default.init()
style_screen_tachobar142_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar142_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar142_main_main_default.set_img_opa(0)

# add style for screen_TachoBar142
screen_TachoBar142.add_style(style_screen_tachobar142_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar143 = lv.img(screen)
screen_TachoBar143.set_pos(3,8)
screen_TachoBar143.set_size(231,78)
screen_TachoBar143.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp944608525.png','rb') as f:
        screen_TachoBar143_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp944608525.png')
    sys.exit()

screen_TachoBar143_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar143_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar143_img_data
})

screen_TachoBar143.set_src(screen_TachoBar143_img)
screen_TachoBar143.set_pivot(0,0)
screen_TachoBar143.set_angle(0)
# create style style_screen_tachobar143_main_main_default
style_screen_tachobar143_main_main_default = lv.style_t()
style_screen_tachobar143_main_main_default.init()
style_screen_tachobar143_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar143_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar143_main_main_default.set_img_opa(0)

# add style for screen_TachoBar143
screen_TachoBar143.add_style(style_screen_tachobar143_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar144 = lv.img(screen)
screen_TachoBar144.set_pos(3,8)
screen_TachoBar144.set_size(231,78)
screen_TachoBar144.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp975628332.png','rb') as f:
        screen_TachoBar144_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp975628332.png')
    sys.exit()

screen_TachoBar144_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar144_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar144_img_data
})

screen_TachoBar144.set_src(screen_TachoBar144_img)
screen_TachoBar144.set_pivot(0,0)
screen_TachoBar144.set_angle(0)
# create style style_screen_tachobar144_main_main_default
style_screen_tachobar144_main_main_default = lv.style_t()
style_screen_tachobar144_main_main_default.init()
style_screen_tachobar144_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar144_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar144_main_main_default.set_img_opa(0)

# add style for screen_TachoBar144
screen_TachoBar144.add_style(style_screen_tachobar144_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar145 = lv.img(screen)
screen_TachoBar145.set_pos(3,8)
screen_TachoBar145.set_size(231,78)
screen_TachoBar145.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp1006648139.png','rb') as f:
        screen_TachoBar145_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp1006648139.png')
    sys.exit()

screen_TachoBar145_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar145_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar145_img_data
})

screen_TachoBar145.set_src(screen_TachoBar145_img)
screen_TachoBar145.set_pivot(0,0)
screen_TachoBar145.set_angle(0)
# create style style_screen_tachobar145_main_main_default
style_screen_tachobar145_main_main_default = lv.style_t()
style_screen_tachobar145_main_main_default.init()
style_screen_tachobar145_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar145_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar145_main_main_default.set_img_opa(0)

# add style for screen_TachoBar145
screen_TachoBar145.add_style(style_screen_tachobar145_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar146 = lv.img(screen)
screen_TachoBar146.set_pos(3,8)
screen_TachoBar146.set_size(231,78)
screen_TachoBar146.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp1689083893.png','rb') as f:
        screen_TachoBar146_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp1689083893.png')
    sys.exit()

screen_TachoBar146_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar146_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar146_img_data
})

screen_TachoBar146.set_src(screen_TachoBar146_img)
screen_TachoBar146.set_pivot(0,0)
screen_TachoBar146.set_angle(0)
# create style style_screen_tachobar146_main_main_default
style_screen_tachobar146_main_main_default = lv.style_t()
style_screen_tachobar146_main_main_default.init()
style_screen_tachobar146_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar146_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar146_main_main_default.set_img_opa(0)

# add style for screen_TachoBar146
screen_TachoBar146.add_style(style_screen_tachobar146_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar147 = lv.img(screen)
screen_TachoBar147.set_pos(3,8)
screen_TachoBar147.set_size(231,78)
screen_TachoBar147.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp1720103700.png','rb') as f:
        screen_TachoBar147_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp1720103700.png')
    sys.exit()

screen_TachoBar147_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar147_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar147_img_data
})

screen_TachoBar147.set_src(screen_TachoBar147_img)
screen_TachoBar147.set_pivot(0,0)
screen_TachoBar147.set_angle(0)
# create style style_screen_tachobar147_main_main_default
style_screen_tachobar147_main_main_default = lv.style_t()
style_screen_tachobar147_main_main_default.init()
style_screen_tachobar147_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar147_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar147_main_main_default.set_img_opa(0)

# add style for screen_TachoBar147
screen_TachoBar147.add_style(style_screen_tachobar147_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar148 = lv.img(screen)
screen_TachoBar148.set_pos(3,8)
screen_TachoBar148.set_size(231,78)
screen_TachoBar148.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp1751123507.png','rb') as f:
        screen_TachoBar148_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp1751123507.png')
    sys.exit()

screen_TachoBar148_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar148_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar148_img_data
})

screen_TachoBar148.set_src(screen_TachoBar148_img)
screen_TachoBar148.set_pivot(0,0)
screen_TachoBar148.set_angle(0)
# create style style_screen_tachobar148_main_main_default
style_screen_tachobar148_main_main_default = lv.style_t()
style_screen_tachobar148_main_main_default.init()
style_screen_tachobar148_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar148_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar148_main_main_default.set_img_opa(0)

# add style for screen_TachoBar148
screen_TachoBar148.add_style(style_screen_tachobar148_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar149 = lv.img(screen)
screen_TachoBar149.set_pos(3,8)
screen_TachoBar149.set_size(231,78)
screen_TachoBar149.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp1782143314.png','rb') as f:
        screen_TachoBar149_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp1782143314.png')
    sys.exit()

screen_TachoBar149_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar149_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar149_img_data
})

screen_TachoBar149.set_src(screen_TachoBar149_img)
screen_TachoBar149.set_pivot(0,0)
screen_TachoBar149.set_angle(0)
# create style style_screen_tachobar149_main_main_default
style_screen_tachobar149_main_main_default = lv.style_t()
style_screen_tachobar149_main_main_default.init()
style_screen_tachobar149_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar149_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar149_main_main_default.set_img_opa(0)

# add style for screen_TachoBar149
screen_TachoBar149.add_style(style_screen_tachobar149_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar150 = lv.img(screen)
screen_TachoBar150.set_pos(3,8)
screen_TachoBar150.set_size(231,78)
screen_TachoBar150.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp1813163121.png','rb') as f:
        screen_TachoBar150_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp1813163121.png')
    sys.exit()

screen_TachoBar150_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar150_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar150_img_data
})

screen_TachoBar150.set_src(screen_TachoBar150_img)
screen_TachoBar150.set_pivot(0,0)
screen_TachoBar150.set_angle(0)
# create style style_screen_tachobar150_main_main_default
style_screen_tachobar150_main_main_default = lv.style_t()
style_screen_tachobar150_main_main_default.init()
style_screen_tachobar150_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar150_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar150_main_main_default.set_img_opa(0)

# add style for screen_TachoBar150
screen_TachoBar150.add_style(style_screen_tachobar150_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar151 = lv.img(screen)
screen_TachoBar151.set_pos(3,8)
screen_TachoBar151.set_size(231,78)
screen_TachoBar151.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp1844182928.png','rb') as f:
        screen_TachoBar151_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp1844182928.png')
    sys.exit()

screen_TachoBar151_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar151_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar151_img_data
})

screen_TachoBar151.set_src(screen_TachoBar151_img)
screen_TachoBar151.set_pivot(0,0)
screen_TachoBar151.set_angle(0)
# create style style_screen_tachobar151_main_main_default
style_screen_tachobar151_main_main_default = lv.style_t()
style_screen_tachobar151_main_main_default.init()
style_screen_tachobar151_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar151_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar151_main_main_default.set_img_opa(0)

# add style for screen_TachoBar151
screen_TachoBar151.add_style(style_screen_tachobar151_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar152 = lv.img(screen)
screen_TachoBar152.set_pos(3,8)
screen_TachoBar152.set_size(231,78)
screen_TachoBar152.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp1875202735.png','rb') as f:
        screen_TachoBar152_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp1875202735.png')
    sys.exit()

screen_TachoBar152_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar152_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar152_img_data
})

screen_TachoBar152.set_src(screen_TachoBar152_img)
screen_TachoBar152.set_pivot(0,0)
screen_TachoBar152.set_angle(0)
# create style style_screen_tachobar152_main_main_default
style_screen_tachobar152_main_main_default = lv.style_t()
style_screen_tachobar152_main_main_default.init()
style_screen_tachobar152_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar152_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar152_main_main_default.set_img_opa(0)

# add style for screen_TachoBar152
screen_TachoBar152.add_style(style_screen_tachobar152_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar153 = lv.img(screen)
screen_TachoBar153.set_pos(3,8)
screen_TachoBar153.set_size(231,78)
screen_TachoBar153.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp1906222542.png','rb') as f:
        screen_TachoBar153_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp1906222542.png')
    sys.exit()

screen_TachoBar153_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar153_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar153_img_data
})

screen_TachoBar153.set_src(screen_TachoBar153_img)
screen_TachoBar153.set_pivot(0,0)
screen_TachoBar153.set_angle(0)
# create style style_screen_tachobar153_main_main_default
style_screen_tachobar153_main_main_default = lv.style_t()
style_screen_tachobar153_main_main_default.init()
style_screen_tachobar153_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar153_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar153_main_main_default.set_img_opa(0)

# add style for screen_TachoBar153
screen_TachoBar153.add_style(style_screen_tachobar153_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar154 = lv.img(screen)
screen_TachoBar154.set_pos(3,8)
screen_TachoBar154.set_size(231,78)
screen_TachoBar154.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp1937242349.png','rb') as f:
        screen_TachoBar154_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp1937242349.png')
    sys.exit()

screen_TachoBar154_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar154_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar154_img_data
})

screen_TachoBar154.set_src(screen_TachoBar154_img)
screen_TachoBar154.set_pivot(0,0)
screen_TachoBar154.set_angle(0)
# create style style_screen_tachobar154_main_main_default
style_screen_tachobar154_main_main_default = lv.style_t()
style_screen_tachobar154_main_main_default.init()
style_screen_tachobar154_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar154_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar154_main_main_default.set_img_opa(0)

# add style for screen_TachoBar154
screen_TachoBar154.add_style(style_screen_tachobar154_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar155 = lv.img(screen)
screen_TachoBar155.set_pos(3,8)
screen_TachoBar155.set_size(231,78)
screen_TachoBar155.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp1968262156.png','rb') as f:
        screen_TachoBar155_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp1968262156.png')
    sys.exit()

screen_TachoBar155_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar155_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar155_img_data
})

screen_TachoBar155.set_src(screen_TachoBar155_img)
screen_TachoBar155.set_pivot(0,0)
screen_TachoBar155.set_angle(0)
# create style style_screen_tachobar155_main_main_default
style_screen_tachobar155_main_main_default = lv.style_t()
style_screen_tachobar155_main_main_default.init()
style_screen_tachobar155_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar155_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar155_main_main_default.set_img_opa(0)

# add style for screen_TachoBar155
screen_TachoBar155.add_style(style_screen_tachobar155_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar156 = lv.img(screen)
screen_TachoBar156.set_pos(3,8)
screen_TachoBar156.set_size(231,78)
screen_TachoBar156.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1644269386.png','rb') as f:
        screen_TachoBar156_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1644269386.png')
    sys.exit()

screen_TachoBar156_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar156_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar156_img_data
})

screen_TachoBar156.set_src(screen_TachoBar156_img)
screen_TachoBar156.set_pivot(0,0)
screen_TachoBar156.set_angle(0)
# create style style_screen_tachobar156_main_main_default
style_screen_tachobar156_main_main_default = lv.style_t()
style_screen_tachobar156_main_main_default.init()
style_screen_tachobar156_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar156_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar156_main_main_default.set_img_opa(0)

# add style for screen_TachoBar156
screen_TachoBar156.add_style(style_screen_tachobar156_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar157 = lv.img(screen)
screen_TachoBar157.set_pos(3,8)
screen_TachoBar157.set_size(231,78)
screen_TachoBar157.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1613249579.png','rb') as f:
        screen_TachoBar157_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1613249579.png')
    sys.exit()

screen_TachoBar157_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar157_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar157_img_data
})

screen_TachoBar157.set_src(screen_TachoBar157_img)
screen_TachoBar157.set_pivot(0,0)
screen_TachoBar157.set_angle(0)
# create style style_screen_tachobar157_main_main_default
style_screen_tachobar157_main_main_default = lv.style_t()
style_screen_tachobar157_main_main_default.init()
style_screen_tachobar157_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar157_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar157_main_main_default.set_img_opa(0)

# add style for screen_TachoBar157
screen_TachoBar157.add_style(style_screen_tachobar157_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar158 = lv.img(screen)
screen_TachoBar158.set_pos(3,8)
screen_TachoBar158.set_size(231,78)
screen_TachoBar158.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1582229772.png','rb') as f:
        screen_TachoBar158_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1582229772.png')
    sys.exit()

screen_TachoBar158_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar158_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar158_img_data
})

screen_TachoBar158.set_src(screen_TachoBar158_img)
screen_TachoBar158.set_pivot(0,0)
screen_TachoBar158.set_angle(0)
# create style style_screen_tachobar158_main_main_default
style_screen_tachobar158_main_main_default = lv.style_t()
style_screen_tachobar158_main_main_default.init()
style_screen_tachobar158_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar158_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar158_main_main_default.set_img_opa(0)

# add style for screen_TachoBar158
screen_TachoBar158.add_style(style_screen_tachobar158_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar159 = lv.img(screen)
screen_TachoBar159.set_pos(3,8)
screen_TachoBar159.set_size(231,78)
screen_TachoBar159.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1551209965.png','rb') as f:
        screen_TachoBar159_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1551209965.png')
    sys.exit()

screen_TachoBar159_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar159_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar159_img_data
})

screen_TachoBar159.set_src(screen_TachoBar159_img)
screen_TachoBar159.set_pivot(0,0)
screen_TachoBar159.set_angle(0)
# create style style_screen_tachobar159_main_main_default
style_screen_tachobar159_main_main_default = lv.style_t()
style_screen_tachobar159_main_main_default.init()
style_screen_tachobar159_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar159_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar159_main_main_default.set_img_opa(0)

# add style for screen_TachoBar159
screen_TachoBar159.add_style(style_screen_tachobar159_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar160 = lv.img(screen)
screen_TachoBar160.set_pos(3,8)
screen_TachoBar160.set_size(231,78)
screen_TachoBar160.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1520190158.png','rb') as f:
        screen_TachoBar160_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1520190158.png')
    sys.exit()

screen_TachoBar160_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar160_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar160_img_data
})

screen_TachoBar160.set_src(screen_TachoBar160_img)
screen_TachoBar160.set_pivot(0,0)
screen_TachoBar160.set_angle(0)
# create style style_screen_tachobar160_main_main_default
style_screen_tachobar160_main_main_default = lv.style_t()
style_screen_tachobar160_main_main_default.init()
style_screen_tachobar160_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar160_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar160_main_main_default.set_img_opa(0)

# add style for screen_TachoBar160
screen_TachoBar160.add_style(style_screen_tachobar160_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar161 = lv.img(screen)
screen_TachoBar161.set_pos(3,8)
screen_TachoBar161.set_size(231,78)
screen_TachoBar161.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1489170351.png','rb') as f:
        screen_TachoBar161_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1489170351.png')
    sys.exit()

screen_TachoBar161_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar161_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar161_img_data
})

screen_TachoBar161.set_src(screen_TachoBar161_img)
screen_TachoBar161.set_pivot(0,0)
screen_TachoBar161.set_angle(0)
# create style style_screen_tachobar161_main_main_default
style_screen_tachobar161_main_main_default = lv.style_t()
style_screen_tachobar161_main_main_default.init()
style_screen_tachobar161_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar161_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar161_main_main_default.set_img_opa(0)

# add style for screen_TachoBar161
screen_TachoBar161.add_style(style_screen_tachobar161_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar162 = lv.img(screen)
screen_TachoBar162.set_pos(3,8)
screen_TachoBar162.set_size(231,78)
screen_TachoBar162.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1458150544.png','rb') as f:
        screen_TachoBar162_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1458150544.png')
    sys.exit()

screen_TachoBar162_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar162_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar162_img_data
})

screen_TachoBar162.set_src(screen_TachoBar162_img)
screen_TachoBar162.set_pivot(0,0)
screen_TachoBar162.set_angle(0)
# create style style_screen_tachobar162_main_main_default
style_screen_tachobar162_main_main_default = lv.style_t()
style_screen_tachobar162_main_main_default.init()
style_screen_tachobar162_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar162_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar162_main_main_default.set_img_opa(0)

# add style for screen_TachoBar162
screen_TachoBar162.add_style(style_screen_tachobar162_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar163 = lv.img(screen)
screen_TachoBar163.set_pos(3,8)
screen_TachoBar163.set_size(231,78)
screen_TachoBar163.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1427130737.png','rb') as f:
        screen_TachoBar163_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1427130737.png')
    sys.exit()

screen_TachoBar163_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar163_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar163_img_data
})

screen_TachoBar163.set_src(screen_TachoBar163_img)
screen_TachoBar163.set_pivot(0,0)
screen_TachoBar163.set_angle(0)
# create style style_screen_tachobar163_main_main_default
style_screen_tachobar163_main_main_default = lv.style_t()
style_screen_tachobar163_main_main_default.init()
style_screen_tachobar163_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar163_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar163_main_main_default.set_img_opa(0)

# add style for screen_TachoBar163
screen_TachoBar163.add_style(style_screen_tachobar163_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar164 = lv.img(screen)
screen_TachoBar164.set_pos(3,8)
screen_TachoBar164.set_size(231,78)
screen_TachoBar164.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1396110930.png','rb') as f:
        screen_TachoBar164_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1396110930.png')
    sys.exit()

screen_TachoBar164_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar164_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar164_img_data
})

screen_TachoBar164.set_src(screen_TachoBar164_img)
screen_TachoBar164.set_pivot(0,0)
screen_TachoBar164.set_angle(0)
# create style style_screen_tachobar164_main_main_default
style_screen_tachobar164_main_main_default = lv.style_t()
style_screen_tachobar164_main_main_default.init()
style_screen_tachobar164_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar164_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar164_main_main_default.set_img_opa(0)

# add style for screen_TachoBar164
screen_TachoBar164.add_style(style_screen_tachobar164_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar165 = lv.img(screen)
screen_TachoBar165.set_pos(3,8)
screen_TachoBar165.set_size(231,78)
screen_TachoBar165.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1365091123.png','rb') as f:
        screen_TachoBar165_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1365091123.png')
    sys.exit()

screen_TachoBar165_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar165_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar165_img_data
})

screen_TachoBar165.set_src(screen_TachoBar165_img)
screen_TachoBar165.set_pivot(0,0)
screen_TachoBar165.set_angle(0)
# create style style_screen_tachobar165_main_main_default
style_screen_tachobar165_main_main_default = lv.style_t()
style_screen_tachobar165_main_main_default.init()
style_screen_tachobar165_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar165_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar165_main_main_default.set_img_opa(0)

# add style for screen_TachoBar165
screen_TachoBar165.add_style(style_screen_tachobar165_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar166 = lv.img(screen)
screen_TachoBar166.set_pos(3,8)
screen_TachoBar166.set_size(231,78)
screen_TachoBar166.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-682655369.png','rb') as f:
        screen_TachoBar166_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-682655369.png')
    sys.exit()

screen_TachoBar166_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar166_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar166_img_data
})

screen_TachoBar166.set_src(screen_TachoBar166_img)
screen_TachoBar166.set_pivot(0,0)
screen_TachoBar166.set_angle(0)
# create style style_screen_tachobar166_main_main_default
style_screen_tachobar166_main_main_default = lv.style_t()
style_screen_tachobar166_main_main_default.init()
style_screen_tachobar166_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar166_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar166_main_main_default.set_img_opa(0)

# add style for screen_TachoBar166
screen_TachoBar166.add_style(style_screen_tachobar166_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar167 = lv.img(screen)
screen_TachoBar167.set_pos(3,8)
screen_TachoBar167.set_size(231,78)
screen_TachoBar167.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-651635562.png','rb') as f:
        screen_TachoBar167_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-651635562.png')
    sys.exit()

screen_TachoBar167_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar167_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar167_img_data
})

screen_TachoBar167.set_src(screen_TachoBar167_img)
screen_TachoBar167.set_pivot(0,0)
screen_TachoBar167.set_angle(0)
# create style style_screen_tachobar167_main_main_default
style_screen_tachobar167_main_main_default = lv.style_t()
style_screen_tachobar167_main_main_default.init()
style_screen_tachobar167_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar167_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar167_main_main_default.set_img_opa(0)

# add style for screen_TachoBar167
screen_TachoBar167.add_style(style_screen_tachobar167_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar168 = lv.img(screen)
screen_TachoBar168.set_pos(3,8)
screen_TachoBar168.set_size(231,78)
screen_TachoBar168.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-620615755.png','rb') as f:
        screen_TachoBar168_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-620615755.png')
    sys.exit()

screen_TachoBar168_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar168_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar168_img_data
})

screen_TachoBar168.set_src(screen_TachoBar168_img)
screen_TachoBar168.set_pivot(0,0)
screen_TachoBar168.set_angle(0)
# create style style_screen_tachobar168_main_main_default
style_screen_tachobar168_main_main_default = lv.style_t()
style_screen_tachobar168_main_main_default.init()
style_screen_tachobar168_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar168_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar168_main_main_default.set_img_opa(0)

# add style for screen_TachoBar168
screen_TachoBar168.add_style(style_screen_tachobar168_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar169 = lv.img(screen)
screen_TachoBar169.set_pos(3,8)
screen_TachoBar169.set_size(231,78)
screen_TachoBar169.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-589595948.png','rb') as f:
        screen_TachoBar169_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-589595948.png')
    sys.exit()

screen_TachoBar169_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar169_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar169_img_data
})

screen_TachoBar169.set_src(screen_TachoBar169_img)
screen_TachoBar169.set_pivot(0,0)
screen_TachoBar169.set_angle(0)
# create style style_screen_tachobar169_main_main_default
style_screen_tachobar169_main_main_default = lv.style_t()
style_screen_tachobar169_main_main_default.init()
style_screen_tachobar169_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar169_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar169_main_main_default.set_img_opa(0)

# add style for screen_TachoBar169
screen_TachoBar169.add_style(style_screen_tachobar169_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar170 = lv.img(screen)
screen_TachoBar170.set_pos(3,8)
screen_TachoBar170.set_size(231,78)
screen_TachoBar170.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-558576141.png','rb') as f:
        screen_TachoBar170_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-558576141.png')
    sys.exit()

screen_TachoBar170_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar170_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar170_img_data
})

screen_TachoBar170.set_src(screen_TachoBar170_img)
screen_TachoBar170.set_pivot(0,0)
screen_TachoBar170.set_angle(0)
# create style style_screen_tachobar170_main_main_default
style_screen_tachobar170_main_main_default = lv.style_t()
style_screen_tachobar170_main_main_default.init()
style_screen_tachobar170_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar170_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar170_main_main_default.set_img_opa(0)

# add style for screen_TachoBar170
screen_TachoBar170.add_style(style_screen_tachobar170_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar171 = lv.img(screen)
screen_TachoBar171.set_pos(3,8)
screen_TachoBar171.set_size(231,78)
screen_TachoBar171.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-527556334.png','rb') as f:
        screen_TachoBar171_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-527556334.png')
    sys.exit()

screen_TachoBar171_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar171_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar171_img_data
})

screen_TachoBar171.set_src(screen_TachoBar171_img)
screen_TachoBar171.set_pivot(0,0)
screen_TachoBar171.set_angle(0)
# create style style_screen_tachobar171_main_main_default
style_screen_tachobar171_main_main_default = lv.style_t()
style_screen_tachobar171_main_main_default.init()
style_screen_tachobar171_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar171_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar171_main_main_default.set_img_opa(0)

# add style for screen_TachoBar171
screen_TachoBar171.add_style(style_screen_tachobar171_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_TachoBar172 = lv.img(screen)
screen_TachoBar172.set_pos(3,8)
screen_TachoBar172.set_size(231,78)
screen_TachoBar172.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-496536527.png','rb') as f:
        screen_TachoBar172_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-496536527.png')
    sys.exit()

screen_TachoBar172_img = lv.img_dsc_t({
  'data_size': len(screen_TachoBar172_img_data),
  'header': {'always_zero': 0, 'w': 231, 'h': 78, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_TachoBar172_img_data
})

screen_TachoBar172.set_src(screen_TachoBar172_img)
screen_TachoBar172.set_pivot(0,0)
screen_TachoBar172.set_angle(0)
# create style style_screen_tachobar172_main_main_default
style_screen_tachobar172_main_main_default = lv.style_t()
style_screen_tachobar172_main_main_default.init()
style_screen_tachobar172_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_tachobar172_main_main_default.set_img_recolor_opa(0)
style_screen_tachobar172_main_main_default.set_img_opa(0)

# add style for screen_TachoBar172
screen_TachoBar172.add_style(style_screen_tachobar172_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_Fuel_Img_Icon = lv.img(screen)
screen_Fuel_Img_Icon.set_pos(105,253)
screen_Fuel_Img_Icon.set_size(30,30)
screen_Fuel_Img_Icon.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp1074127769.png','rb') as f:
        screen_Fuel_Img_Icon_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp1074127769.png')
    sys.exit()

screen_Fuel_Img_Icon_img = lv.img_dsc_t({
  'data_size': len(screen_Fuel_Img_Icon_img_data),
  'header': {'always_zero': 0, 'w': 30, 'h': 30, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_Fuel_Img_Icon_img_data
})

screen_Fuel_Img_Icon.set_src(screen_Fuel_Img_Icon_img)
screen_Fuel_Img_Icon.set_pivot(0,0)
screen_Fuel_Img_Icon.set_angle(0)
# create style style_screen_fuel_img_icon_main_main_default
style_screen_fuel_img_icon_main_main_default = lv.style_t()
style_screen_fuel_img_icon_main_main_default.init()
style_screen_fuel_img_icon_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_fuel_img_icon_main_main_default.set_img_recolor_opa(0)
style_screen_fuel_img_icon_main_main_default.set_img_opa(0)

# add style for screen_Fuel_Img_Icon
screen_Fuel_Img_Icon.add_style(style_screen_fuel_img_icon_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_imgOilTelltale = lv.imgbtn(screen)
screen_imgOilTelltale.set_pos(6,291)
screen_imgOilTelltale.set_size(32,13)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp1312483137.png','rb') as f:
        screen_imgOilTelltale_imgReleased_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp1312483137.png')
    sys.exit()

screen_imgOilTelltale_imgReleased = lv.img_dsc_t({
  'data_size': len(screen_imgOilTelltale_imgReleased_data),
  'header': {'always_zero': 0, 'w': 32, 'h': 13, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_imgOilTelltale_imgReleased_data
})
screen_imgOilTelltale.set_src(lv.imgbtn.STATE.RELEASED, screen_imgOilTelltale_imgReleased, None, None)

try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-2059009200.png','rb') as f:
        screen_imgOilTelltale_imgPressed_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-2059009200.png')
    sys.exit()

screen_imgOilTelltale_imgPressed = lv.img_dsc_t({
  'data_size': len(screen_imgOilTelltale_imgPressed_data),
  'header': {'always_zero': 0, 'w': 32, 'h': 13, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_imgOilTelltale_imgPressed_data
})
screen_imgOilTelltale.set_src(lv.imgbtn.STATE.PRESSED, screen_imgOilTelltale_imgPressed, None, None)




screen_imgOilTelltale.add_flag(lv.obj.FLAG.CHECKABLE)
# create style style_screen_imgoiltelltale_main_main_default
style_screen_imgoiltelltale_main_main_default = lv.style_t()
style_screen_imgoiltelltale_main_main_default.init()
style_screen_imgoiltelltale_main_main_default.set_text_color(lv.color_make(0x00,0x00,0x00))
try:
    style_screen_imgoiltelltale_main_main_default.set_text_font(lv.font_simsun_12)
except AttributeError:
    try:
        style_screen_imgoiltelltale_main_main_default.set_text_font(lv.font_montserrat_12)
    except AttributeError:
        style_screen_imgoiltelltale_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_imgoiltelltale_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_imgoiltelltale_main_main_default.set_img_recolor_opa(0)
style_screen_imgoiltelltale_main_main_default.set_img_opa(254)

# add style for screen_imgOilTelltale
screen_imgOilTelltale.add_style(style_screen_imgoiltelltale_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_screen_imgoiltelltale_main_main_pressed
style_screen_imgoiltelltale_main_main_pressed = lv.style_t()
style_screen_imgoiltelltale_main_main_pressed.init()
style_screen_imgoiltelltale_main_main_pressed.set_text_color(lv.color_make(0xFF,0x33,0xFF))
try:
    style_screen_imgoiltelltale_main_main_pressed.set_text_font(lv.font_simsun_16)
except AttributeError:
    try:
        style_screen_imgoiltelltale_main_main_pressed.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_screen_imgoiltelltale_main_main_pressed.set_text_font(lv.font_montserrat_16)
style_screen_imgoiltelltale_main_main_pressed.set_img_recolor(lv.color_make(0x00,0x00,0x00))
style_screen_imgoiltelltale_main_main_pressed.set_img_recolor_opa(0)

# add style for screen_imgOilTelltale
screen_imgOilTelltale.add_style(style_screen_imgoiltelltale_main_main_pressed, lv.PART.MAIN|lv.STATE.PRESSED)

# create style style_screen_imgoiltelltale_main_main_checked
style_screen_imgoiltelltale_main_main_checked = lv.style_t()
style_screen_imgoiltelltale_main_main_checked.init()
style_screen_imgoiltelltale_main_main_checked.set_text_color(lv.color_make(0xFF,0x33,0xFF))
try:
    style_screen_imgoiltelltale_main_main_checked.set_text_font(lv.font_simsun_16)
except AttributeError:
    try:
        style_screen_imgoiltelltale_main_main_checked.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_screen_imgoiltelltale_main_main_checked.set_text_font(lv.font_montserrat_16)
style_screen_imgoiltelltale_main_main_checked.set_img_recolor(lv.color_make(0x00,0x00,0x00))
style_screen_imgoiltelltale_main_main_checked.set_img_recolor_opa(0)

# add style for screen_imgOilTelltale
screen_imgOilTelltale.add_style(style_screen_imgoiltelltale_main_main_checked, lv.PART.MAIN|lv.STATE.CHECKED)

screen_Sub_Button = lv.imgbtn(screen)
screen_Sub_Button.set_pos(204,151)
screen_Sub_Button.set_size(20,20)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1198168671.png','rb') as f:
        screen_Sub_Button_imgReleased_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1198168671.png')
    sys.exit()

screen_Sub_Button_imgReleased = lv.img_dsc_t({
  'data_size': len(screen_Sub_Button_imgReleased_data),
  'header': {'always_zero': 0, 'w': 20, 'h': 20, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_Sub_Button_imgReleased_data
})
screen_Sub_Button.set_src(lv.imgbtn.STATE.RELEASED, screen_Sub_Button_imgReleased, None, None)

try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-723275381.png','rb') as f:
        screen_Sub_Button_imgPressed_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-723275381.png')
    sys.exit()

screen_Sub_Button_imgPressed = lv.img_dsc_t({
  'data_size': len(screen_Sub_Button_imgPressed_data),
  'header': {'always_zero': 0, 'w': 20, 'h': 20, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_Sub_Button_imgPressed_data
})
screen_Sub_Button.set_src(lv.imgbtn.STATE.PRESSED, screen_Sub_Button_imgPressed, None, None)




screen_Sub_Button.add_flag(lv.obj.FLAG.CHECKABLE)
# create style style_screen_sub_button_main_main_default
style_screen_sub_button_main_main_default = lv.style_t()
style_screen_sub_button_main_main_default.init()
style_screen_sub_button_main_main_default.set_text_color(lv.color_make(0x00,0x00,0x00))
try:
    style_screen_sub_button_main_main_default.set_text_font(lv.font_simsun_12)
except AttributeError:
    try:
        style_screen_sub_button_main_main_default.set_text_font(lv.font_montserrat_12)
    except AttributeError:
        style_screen_sub_button_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_sub_button_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_sub_button_main_main_default.set_img_recolor_opa(0)
style_screen_sub_button_main_main_default.set_img_opa(255)

# add style for screen_Sub_Button
screen_Sub_Button.add_style(style_screen_sub_button_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_screen_sub_button_main_main_pressed
style_screen_sub_button_main_main_pressed = lv.style_t()
style_screen_sub_button_main_main_pressed.init()
style_screen_sub_button_main_main_pressed.set_text_color(lv.color_make(0xFF,0x33,0xFF))
try:
    style_screen_sub_button_main_main_pressed.set_text_font(lv.font_simsun_16)
except AttributeError:
    try:
        style_screen_sub_button_main_main_pressed.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_screen_sub_button_main_main_pressed.set_text_font(lv.font_montserrat_16)
style_screen_sub_button_main_main_pressed.set_img_recolor(lv.color_make(0x00,0x00,0x00))
style_screen_sub_button_main_main_pressed.set_img_recolor_opa(0)

# add style for screen_Sub_Button
screen_Sub_Button.add_style(style_screen_sub_button_main_main_pressed, lv.PART.MAIN|lv.STATE.PRESSED)

# create style style_screen_sub_button_main_main_checked
style_screen_sub_button_main_main_checked = lv.style_t()
style_screen_sub_button_main_main_checked.init()
style_screen_sub_button_main_main_checked.set_text_color(lv.color_make(0xFF,0x33,0xFF))
try:
    style_screen_sub_button_main_main_checked.set_text_font(lv.font_simsun_16)
except AttributeError:
    try:
        style_screen_sub_button_main_main_checked.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_screen_sub_button_main_main_checked.set_text_font(lv.font_montserrat_16)
style_screen_sub_button_main_main_checked.set_img_recolor(lv.color_make(0x00,0x00,0x00))
style_screen_sub_button_main_main_checked.set_img_recolor_opa(0)

# add style for screen_Sub_Button
screen_Sub_Button.add_style(style_screen_sub_button_main_main_checked, lv.PART.MAIN|lv.STATE.CHECKED)

screen_Sub_Button_Intermediatae = lv.img(screen)
screen_Sub_Button_Intermediatae.set_pos(204,151)
screen_Sub_Button_Intermediatae.set_size(20,20)
screen_Sub_Button_Intermediatae.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1198168671.png','rb') as f:
        screen_Sub_Button_Intermediatae_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1198168671.png')
    sys.exit()

screen_Sub_Button_Intermediatae_img = lv.img_dsc_t({
  'data_size': len(screen_Sub_Button_Intermediatae_img_data),
  'header': {'always_zero': 0, 'w': 20, 'h': 20, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_Sub_Button_Intermediatae_img_data
})

screen_Sub_Button_Intermediatae.set_src(screen_Sub_Button_Intermediatae_img)
screen_Sub_Button_Intermediatae.set_pivot(0,0)
screen_Sub_Button_Intermediatae.set_angle(0)
# create style style_screen_sub_button_intermediatae_main_main_default
style_screen_sub_button_intermediatae_main_main_default = lv.style_t()
style_screen_sub_button_intermediatae_main_main_default.init()
style_screen_sub_button_intermediatae_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_sub_button_intermediatae_main_main_default.set_img_recolor_opa(0)
style_screen_sub_button_intermediatae_main_main_default.set_img_opa(255)

# add style for screen_Sub_Button_Intermediatae
screen_Sub_Button_Intermediatae.add_style(style_screen_sub_button_intermediatae_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_Clock_Am = lv.label(screen)
screen_Clock_Am.set_pos(124,81)
screen_Clock_Am.set_size(16,12)
screen_Clock_Am.set_text("Am")
screen_Clock_Am.set_long_mode(lv.label.LONG.WRAP)
screen_Clock_Am.set_style_text_align(lv.TEXT_ALIGN.CENTER, 0)
# create style style_screen_clock_am_main_main_default
style_screen_clock_am_main_main_default = lv.style_t()
style_screen_clock_am_main_main_default.init()
style_screen_clock_am_main_main_default.set_radius(0)
style_screen_clock_am_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_screen_clock_am_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_clock_am_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_screen_clock_am_main_main_default.set_bg_opa(0)
style_screen_clock_am_main_main_default.set_text_color(lv.color_make(0xfa,0xfa,0xfa))
try:
    style_screen_clock_am_main_main_default.set_text_font(lv.font_FjallaOne_Regular_17)
except AttributeError:
    try:
        style_screen_clock_am_main_main_default.set_text_font(lv.font_montserrat_17)
    except AttributeError:
        style_screen_clock_am_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_clock_am_main_main_default.set_text_letter_space(2)
style_screen_clock_am_main_main_default.set_pad_left(0)
style_screen_clock_am_main_main_default.set_pad_right(0)
style_screen_clock_am_main_main_default.set_pad_top(0)
style_screen_clock_am_main_main_default.set_pad_bottom(0)

# add style for screen_Clock_Am
screen_Clock_Am.add_style(style_screen_clock_am_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_Music_Icon = lv.img(screen)
screen_Music_Icon.set_pos(105,252)
screen_Music_Icon.set_size(30,30)
screen_Music_Icon.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp541698585.png','rb') as f:
        screen_Music_Icon_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp541698585.png')
    sys.exit()

screen_Music_Icon_img = lv.img_dsc_t({
  'data_size': len(screen_Music_Icon_img_data),
  'header': {'always_zero': 0, 'w': 30, 'h': 30, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_Music_Icon_img_data
})

screen_Music_Icon.set_src(screen_Music_Icon_img)
screen_Music_Icon.set_pivot(0,0)
screen_Music_Icon.set_angle(0)
# create style style_screen_music_icon_main_main_default
style_screen_music_icon_main_main_default = lv.style_t()
style_screen_music_icon_main_main_default.init()
style_screen_music_icon_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_music_icon_main_main_default.set_img_recolor_opa(0)
style_screen_music_icon_main_main_default.set_img_opa(0)

# add style for screen_Music_Icon
screen_Music_Icon.add_style(style_screen_music_icon_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_Slider = lv.slider(screen)
screen_Slider.set_pos(55,240)
screen_Slider.set_size(137,2)
screen_Slider.set_range(0, 100)
screen_Slider.set_value(50, False)

# create style style_screen_slider_main_main_default
style_screen_slider_main_main_default = lv.style_t()
style_screen_slider_main_main_default.init()
style_screen_slider_main_main_default.set_radius(50)
style_screen_slider_main_main_default.set_bg_color(lv.color_make(0xff,0xff,0xff))
style_screen_slider_main_main_default.set_bg_grad_color(lv.color_make(0xff,0xff,0xff))
style_screen_slider_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_screen_slider_main_main_default.set_bg_opa(255)
style_screen_slider_main_main_default.set_outline_color(lv.color_make(0x21,0x95,0xf6))
style_screen_slider_main_main_default.set_outline_width(0)
style_screen_slider_main_main_default.set_outline_opa(0)
style_screen_slider_main_main_default.set_pad_left(0)
style_screen_slider_main_main_default.set_pad_right(0)
style_screen_slider_main_main_default.set_pad_top(0)
style_screen_slider_main_main_default.set_pad_bottom(0)

# add style for screen_Slider
screen_Slider.add_style(style_screen_slider_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_screen_slider_main_indicator_default
style_screen_slider_main_indicator_default = lv.style_t()
style_screen_slider_main_indicator_default.init()
style_screen_slider_main_indicator_default.set_radius(50)
style_screen_slider_main_indicator_default.set_bg_color(lv.color_make(0xf6,0x93,0x23))
style_screen_slider_main_indicator_default.set_bg_grad_color(lv.color_make(0xf6,0x57,0x23))
style_screen_slider_main_indicator_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_screen_slider_main_indicator_default.set_bg_opa(255)

# add style for screen_Slider
screen_Slider.add_style(style_screen_slider_main_indicator_default, lv.PART.INDICATOR|lv.STATE.DEFAULT)

# create style style_screen_slider_main_knob_default
style_screen_slider_main_knob_default = lv.style_t()
style_screen_slider_main_knob_default.init()
style_screen_slider_main_knob_default.set_radius(50)
style_screen_slider_main_knob_default.set_bg_color(lv.color_make(0xff,0xff,0xff))
style_screen_slider_main_knob_default.set_bg_grad_color(lv.color_make(0xff,0xff,0xff))
style_screen_slider_main_knob_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_screen_slider_main_knob_default.set_bg_opa(255)

# add style for screen_Slider
screen_Slider.add_style(style_screen_slider_main_knob_default, lv.PART.KNOB|lv.STATE.DEFAULT)

screen_x1000RPM_Img = lv.img(screen)
screen_x1000RPM_Img.set_pos(95,52)
screen_x1000RPM_Img.set_size(49,13)
screen_x1000RPM_Img.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1015064343.png','rb') as f:
        screen_x1000RPM_Img_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1015064343.png')
    sys.exit()

screen_x1000RPM_Img_img = lv.img_dsc_t({
  'data_size': len(screen_x1000RPM_Img_img_data),
  'header': {'always_zero': 0, 'w': 49, 'h': 13, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_x1000RPM_Img_img_data
})

screen_x1000RPM_Img.set_src(screen_x1000RPM_Img_img)
screen_x1000RPM_Img.set_pivot(0,0)
screen_x1000RPM_Img.set_angle(0)
# create style style_screen_x1000rpm_img_main_main_default
style_screen_x1000rpm_img_main_main_default = lv.style_t()
style_screen_x1000rpm_img_main_main_default.init()
style_screen_x1000rpm_img_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_x1000rpm_img_main_main_default.set_img_recolor_opa(0)
style_screen_x1000rpm_img_main_main_default.set_img_opa(255)

# add style for screen_x1000RPM_Img
screen_x1000RPM_Img.add_style(style_screen_x1000rpm_img_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_E_F_Img = lv.img(screen)
screen_E_F_Img.set_pos(38,254)
screen_E_F_Img.set_size(13,15)
screen_E_F_Img.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp171756376.png','rb') as f:
        screen_E_F_Img_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp171756376.png')
    sys.exit()

screen_E_F_Img_img = lv.img_dsc_t({
  'data_size': len(screen_E_F_Img_img_data),
  'header': {'always_zero': 0, 'w': 13, 'h': 15, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_E_F_Img_img_data
})

screen_E_F_Img.set_src(screen_E_F_Img_img)
screen_E_F_Img.set_pivot(0,0)
screen_E_F_Img.set_angle(0)
# create style style_screen_e_f_img_main_main_default
style_screen_e_f_img_main_main_default = lv.style_t()
style_screen_e_f_img_main_main_default.init()
style_screen_e_f_img_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_e_f_img_main_main_default.set_img_recolor_opa(0)
style_screen_e_f_img_main_main_default.set_img_opa(255)

# add style for screen_E_F_Img
screen_E_F_Img.add_style(style_screen_e_f_img_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_F_Img = lv.img(screen)
screen_F_Img.set_pos(190,252)
screen_F_Img.set_size(10,16)
screen_F_Img.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp1981272343.png','rb') as f:
        screen_F_Img_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp1981272343.png')
    sys.exit()

screen_F_Img_img = lv.img_dsc_t({
  'data_size': len(screen_F_Img_img_data),
  'header': {'always_zero': 0, 'w': 10, 'h': 16, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_F_Img_img_data
})

screen_F_Img.set_src(screen_F_Img_img)
screen_F_Img.set_pivot(0,0)
screen_F_Img.set_angle(0)
# create style style_screen_f_img_main_main_default
style_screen_f_img_main_main_default = lv.style_t()
style_screen_f_img_main_main_default.init()
style_screen_f_img_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_f_img_main_main_default.set_img_recolor_opa(0)
style_screen_f_img_main_main_default.set_img_opa(255)

# add style for screen_F_Img
screen_F_Img.add_style(style_screen_f_img_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_Fuel_low_mMarker = lv.img(screen)
screen_Fuel_low_mMarker.set_pos(35,276)
screen_Fuel_low_mMarker.set_size(11,13)
screen_Fuel_low_mMarker.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-120526854.png','rb') as f:
        screen_Fuel_low_mMarker_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-120526854.png')
    sys.exit()

screen_Fuel_low_mMarker_img = lv.img_dsc_t({
  'data_size': len(screen_Fuel_low_mMarker_img_data),
  'header': {'always_zero': 0, 'w': 11, 'h': 13, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_Fuel_low_mMarker_img_data
})

screen_Fuel_low_mMarker.set_src(screen_Fuel_low_mMarker_img)
screen_Fuel_low_mMarker.set_pivot(0,0)
screen_Fuel_low_mMarker.set_angle(0)
# create style style_screen_fuel_low_mmarker_main_main_default
style_screen_fuel_low_mmarker_main_main_default = lv.style_t()
style_screen_fuel_low_mmarker_main_main_default.init()
style_screen_fuel_low_mmarker_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_fuel_low_mmarker_main_main_default.set_img_recolor_opa(0)
style_screen_fuel_low_mmarker_main_main_default.set_img_opa(255)

# add style for screen_Fuel_low_mMarker
screen_Fuel_low_mMarker.add_style(style_screen_fuel_low_mmarker_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_Batt_Outline = lv.img(screen)
screen_Batt_Outline.set_pos(26,111)
screen_Batt_Outline.set_size(20,12)
screen_Batt_Outline.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp2008703252.png','rb') as f:
        screen_Batt_Outline_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp2008703252.png')
    sys.exit()

screen_Batt_Outline_img = lv.img_dsc_t({
  'data_size': len(screen_Batt_Outline_img_data),
  'header': {'always_zero': 0, 'w': 20, 'h': 12, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_Batt_Outline_img_data
})

screen_Batt_Outline.set_src(screen_Batt_Outline_img)
screen_Batt_Outline.set_pivot(0,0)
screen_Batt_Outline.set_angle(0)
# create style style_screen_batt_outline_main_main_default
style_screen_batt_outline_main_main_default = lv.style_t()
style_screen_batt_outline_main_main_default.init()
style_screen_batt_outline_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_batt_outline_main_main_default.set_img_recolor_opa(0)
style_screen_batt_outline_main_main_default.set_img_opa(255)

# add style for screen_Batt_Outline
screen_Batt_Outline.add_style(style_screen_batt_outline_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_Batt_1 = lv.img(screen)
screen_Batt_1.set_pos(28,113)
screen_Batt_1.set_size(3,8)
# create style style_screen_batt_1_main_main_default
style_screen_batt_1_main_main_default = lv.style_t()
style_screen_batt_1_main_main_default.init()
style_screen_batt_1_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_batt_1_main_main_default.set_img_recolor_opa(0)
style_screen_batt_1_main_main_default.set_img_opa(255)

# add style for screen_Batt_1
screen_Batt_1.add_style(style_screen_batt_1_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_Batt_2 = lv.img(screen)
screen_Batt_2.set_pos(32,113)
screen_Batt_2.set_size(3,8)
screen_Batt_2.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1868359478.png','rb') as f:
        screen_Batt_2_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1868359478.png')
    sys.exit()

screen_Batt_2_img = lv.img_dsc_t({
  'data_size': len(screen_Batt_2_img_data),
  'header': {'always_zero': 0, 'w': 3, 'h': 8, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_Batt_2_img_data
})

screen_Batt_2.set_src(screen_Batt_2_img)
screen_Batt_2.set_pivot(0,0)
screen_Batt_2.set_angle(0)
# create style style_screen_batt_2_main_main_default
style_screen_batt_2_main_main_default = lv.style_t()
style_screen_batt_2_main_main_default.init()
style_screen_batt_2_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_batt_2_main_main_default.set_img_recolor_opa(0)
style_screen_batt_2_main_main_default.set_img_opa(255)

# add style for screen_Batt_2
screen_Batt_2.add_style(style_screen_batt_2_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_Batt_3 = lv.img(screen)
screen_Batt_3.set_pos(36,113)
screen_Batt_3.set_size(3,8)
screen_Batt_3.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1868359478.png','rb') as f:
        screen_Batt_3_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1868359478.png')
    sys.exit()

screen_Batt_3_img = lv.img_dsc_t({
  'data_size': len(screen_Batt_3_img_data),
  'header': {'always_zero': 0, 'w': 3, 'h': 8, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_Batt_3_img_data
})

screen_Batt_3.set_src(screen_Batt_3_img)
screen_Batt_3.set_pivot(0,0)
screen_Batt_3.set_angle(0)
# create style style_screen_batt_3_main_main_default
style_screen_batt_3_main_main_default = lv.style_t()
style_screen_batt_3_main_main_default.init()
style_screen_batt_3_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_batt_3_main_main_default.set_img_recolor_opa(0)
style_screen_batt_3_main_main_default.set_img_opa(255)

# add style for screen_Batt_3
screen_Batt_3.add_style(style_screen_batt_3_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_Batt_4 = lv.img(screen)
screen_Batt_4.set_pos(40,113)
screen_Batt_4.set_size(3,8)
screen_Batt_4.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp621169484.png','rb') as f:
        screen_Batt_4_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp621169484.png')
    sys.exit()

screen_Batt_4_img = lv.img_dsc_t({
  'data_size': len(screen_Batt_4_img_data),
  'header': {'always_zero': 0, 'w': 3, 'h': 8, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_Batt_4_img_data
})

screen_Batt_4.set_src(screen_Batt_4_img)
screen_Batt_4.set_pivot(0,0)
screen_Batt_4.set_angle(0)
# create style style_screen_batt_4_main_main_default
style_screen_batt_4_main_main_default = lv.style_t()
style_screen_batt_4_main_main_default.init()
style_screen_batt_4_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_batt_4_main_main_default.set_img_recolor_opa(0)
style_screen_batt_4_main_main_default.set_img_opa(255)

# add style for screen_Batt_4
screen_Batt_4.add_style(style_screen_batt_4_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_Signal_1 = lv.img(screen)
screen_Signal_1.set_pos(200,119)
screen_Signal_1.set_size(2,4)
screen_Signal_1.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1986661283.png','rb') as f:
        screen_Signal_1_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1986661283.png')
    sys.exit()

screen_Signal_1_img = lv.img_dsc_t({
  'data_size': len(screen_Signal_1_img_data),
  'header': {'always_zero': 0, 'w': 2, 'h': 4, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_Signal_1_img_data
})

screen_Signal_1.set_src(screen_Signal_1_img)
screen_Signal_1.set_pivot(0,0)
screen_Signal_1.set_angle(0)
# create style style_screen_signal_1_main_main_default
style_screen_signal_1_main_main_default = lv.style_t()
style_screen_signal_1_main_main_default.init()
style_screen_signal_1_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_signal_1_main_main_default.set_img_recolor_opa(0)
style_screen_signal_1_main_main_default.set_img_opa(255)

# add style for screen_Signal_1
screen_Signal_1.add_style(style_screen_signal_1_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_Signal2 = lv.img(screen)
screen_Signal2.set_pos(204,117)
screen_Signal2.set_size(2,6)
screen_Signal2.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp719958111.png','rb') as f:
        screen_Signal2_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp719958111.png')
    sys.exit()

screen_Signal2_img = lv.img_dsc_t({
  'data_size': len(screen_Signal2_img_data),
  'header': {'always_zero': 0, 'w': 2, 'h': 6, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_Signal2_img_data
})

screen_Signal2.set_src(screen_Signal2_img)
screen_Signal2.set_pivot(0,0)
screen_Signal2.set_angle(0)
# create style style_screen_signal2_main_main_default
style_screen_signal2_main_main_default = lv.style_t()
style_screen_signal2_main_main_default.init()
style_screen_signal2_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_signal2_main_main_default.set_img_recolor_opa(0)
style_screen_signal2_main_main_default.set_img_opa(255)

# add style for screen_Signal2
screen_Signal2.add_style(style_screen_signal2_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_Signal_3 = lv.img(screen)
screen_Signal_3.set_pos(208,114)
screen_Signal_3.set_size(2,9)
screen_Signal_3.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp484919906.png','rb') as f:
        screen_Signal_3_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp484919906.png')
    sys.exit()

screen_Signal_3_img = lv.img_dsc_t({
  'data_size': len(screen_Signal_3_img_data),
  'header': {'always_zero': 0, 'w': 2, 'h': 9, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_Signal_3_img_data
})

screen_Signal_3.set_src(screen_Signal_3_img)
screen_Signal_3.set_pivot(0,0)
screen_Signal_3.set_angle(0)
# create style style_screen_signal_3_main_main_default
style_screen_signal_3_main_main_default = lv.style_t()
style_screen_signal_3_main_main_default.init()
style_screen_signal_3_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_signal_3_main_main_default.set_img_recolor_opa(0)
style_screen_signal_3_main_main_default.set_img_opa(255)

# add style for screen_Signal_3
screen_Signal_3.add_style(style_screen_signal_3_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_Signal_4 = lv.img(screen)
screen_Signal_4.set_pos(212,111)
screen_Signal_4.set_size(2,12)
screen_Signal_4.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-961628190.png','rb') as f:
        screen_Signal_4_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-961628190.png')
    sys.exit()

screen_Signal_4_img = lv.img_dsc_t({
  'data_size': len(screen_Signal_4_img_data),
  'header': {'always_zero': 0, 'w': 2, 'h': 12, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_Signal_4_img_data
})

screen_Signal_4.set_src(screen_Signal_4_img)
screen_Signal_4.set_pivot(0,0)
screen_Signal_4.set_angle(0)
# create style style_screen_signal_4_main_main_default
style_screen_signal_4_main_main_default = lv.style_t()
style_screen_signal_4_main_main_default.init()
style_screen_signal_4_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_signal_4_main_main_default.set_img_recolor_opa(0)
style_screen_signal_4_main_main_default.set_img_opa(255)

# add style for screen_Signal_4
screen_Signal_4.add_style(style_screen_signal_4_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_Signal_1_Nobar = lv.img(screen)
screen_Signal_1_Nobar.set_pos(200,119)
screen_Signal_1_Nobar.set_size(2,4)
screen_Signal_1_Nobar.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1986661283.png','rb') as f:
        screen_Signal_1_Nobar_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1986661283.png')
    sys.exit()

screen_Signal_1_Nobar_img = lv.img_dsc_t({
  'data_size': len(screen_Signal_1_Nobar_img_data),
  'header': {'always_zero': 0, 'w': 2, 'h': 4, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_Signal_1_Nobar_img_data
})

screen_Signal_1_Nobar.set_src(screen_Signal_1_Nobar_img)
screen_Signal_1_Nobar.set_pivot(0,0)
screen_Signal_1_Nobar.set_angle(0)
# create style style_screen_signal_1_nobar_main_main_default
style_screen_signal_1_nobar_main_main_default = lv.style_t()
style_screen_signal_1_nobar_main_main_default.init()
style_screen_signal_1_nobar_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_signal_1_nobar_main_main_default.set_img_recolor_opa(0)
style_screen_signal_1_nobar_main_main_default.set_img_opa(50)

# add style for screen_Signal_1_Nobar
screen_Signal_1_Nobar.add_style(style_screen_signal_1_nobar_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_Signal_2_Nobar = lv.img(screen)
screen_Signal_2_Nobar.set_pos(204,117)
screen_Signal_2_Nobar.set_size(2,6)
screen_Signal_2_Nobar.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp719958111.png','rb') as f:
        screen_Signal_2_Nobar_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp719958111.png')
    sys.exit()

screen_Signal_2_Nobar_img = lv.img_dsc_t({
  'data_size': len(screen_Signal_2_Nobar_img_data),
  'header': {'always_zero': 0, 'w': 2, 'h': 6, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_Signal_2_Nobar_img_data
})

screen_Signal_2_Nobar.set_src(screen_Signal_2_Nobar_img)
screen_Signal_2_Nobar.set_pivot(0,0)
screen_Signal_2_Nobar.set_angle(0)
# create style style_screen_signal_2_nobar_main_main_default
style_screen_signal_2_nobar_main_main_default = lv.style_t()
style_screen_signal_2_nobar_main_main_default.init()
style_screen_signal_2_nobar_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_signal_2_nobar_main_main_default.set_img_recolor_opa(0)
style_screen_signal_2_nobar_main_main_default.set_img_opa(51)

# add style for screen_Signal_2_Nobar
screen_Signal_2_Nobar.add_style(style_screen_signal_2_nobar_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_Signal_3_Nobar = lv.img(screen)
screen_Signal_3_Nobar.set_pos(208,114)
screen_Signal_3_Nobar.set_size(2,9)
screen_Signal_3_Nobar.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp484919906.png','rb') as f:
        screen_Signal_3_Nobar_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp484919906.png')
    sys.exit()

screen_Signal_3_Nobar_img = lv.img_dsc_t({
  'data_size': len(screen_Signal_3_Nobar_img_data),
  'header': {'always_zero': 0, 'w': 2, 'h': 9, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_Signal_3_Nobar_img_data
})

screen_Signal_3_Nobar.set_src(screen_Signal_3_Nobar_img)
screen_Signal_3_Nobar.set_pivot(0,0)
screen_Signal_3_Nobar.set_angle(0)
# create style style_screen_signal_3_nobar_main_main_default
style_screen_signal_3_nobar_main_main_default = lv.style_t()
style_screen_signal_3_nobar_main_main_default.init()
style_screen_signal_3_nobar_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_signal_3_nobar_main_main_default.set_img_recolor_opa(0)
style_screen_signal_3_nobar_main_main_default.set_img_opa(50)

# add style for screen_Signal_3_Nobar
screen_Signal_3_Nobar.add_style(style_screen_signal_3_nobar_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_Signal_4_Nobar = lv.img(screen)
screen_Signal_4_Nobar.set_pos(212,111)
screen_Signal_4_Nobar.set_size(2,12)
screen_Signal_4_Nobar.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-961628190.png','rb') as f:
        screen_Signal_4_Nobar_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-961628190.png')
    sys.exit()

screen_Signal_4_Nobar_img = lv.img_dsc_t({
  'data_size': len(screen_Signal_4_Nobar_img_data),
  'header': {'always_zero': 0, 'w': 2, 'h': 12, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_Signal_4_Nobar_img_data
})

screen_Signal_4_Nobar.set_src(screen_Signal_4_Nobar_img)
screen_Signal_4_Nobar.set_pivot(0,0)
screen_Signal_4_Nobar.set_angle(0)
# create style style_screen_signal_4_nobar_main_main_default
style_screen_signal_4_nobar_main_main_default = lv.style_t()
style_screen_signal_4_nobar_main_main_default.init()
style_screen_signal_4_nobar_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_signal_4_nobar_main_main_default.set_img_recolor_opa(0)
style_screen_signal_4_nobar_main_main_default.set_img_opa(51)

# add style for screen_Signal_4_Nobar
screen_Signal_4_Nobar.add_style(style_screen_signal_4_nobar_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_Battery_1 = lv.img(screen)
screen_Battery_1.set_pos(28,113)
screen_Battery_1.set_size(3,8)
screen_Battery_1.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1865462144.png','rb') as f:
        screen_Battery_1_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1865462144.png')
    sys.exit()

screen_Battery_1_img = lv.img_dsc_t({
  'data_size': len(screen_Battery_1_img_data),
  'header': {'always_zero': 0, 'w': 3, 'h': 8, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_Battery_1_img_data
})

screen_Battery_1.set_src(screen_Battery_1_img)
screen_Battery_1.set_pivot(0,0)
screen_Battery_1.set_angle(0)
# create style style_screen_battery_1_main_main_default
style_screen_battery_1_main_main_default = lv.style_t()
style_screen_battery_1_main_main_default.init()
style_screen_battery_1_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_battery_1_main_main_default.set_img_recolor_opa(0)
style_screen_battery_1_main_main_default.set_img_opa(255)

# add style for screen_Battery_1
screen_Battery_1.add_style(style_screen_battery_1_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_Contacts_Icon = lv.img(screen)
screen_Contacts_Icon.set_pos(103,248)
screen_Contacts_Icon.set_size(34,34)
screen_Contacts_Icon.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp1982228721.png','rb') as f:
        screen_Contacts_Icon_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp1982228721.png')
    sys.exit()

screen_Contacts_Icon_img = lv.img_dsc_t({
  'data_size': len(screen_Contacts_Icon_img_data),
  'header': {'always_zero': 0, 'w': 34, 'h': 34, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_Contacts_Icon_img_data
})

screen_Contacts_Icon.set_src(screen_Contacts_Icon_img)
screen_Contacts_Icon.set_pivot(0,0)
screen_Contacts_Icon.set_angle(0)
# create style style_screen_contacts_icon_main_main_default
style_screen_contacts_icon_main_main_default = lv.style_t()
style_screen_contacts_icon_main_main_default.init()
style_screen_contacts_icon_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_contacts_icon_main_main_default.set_img_recolor_opa(0)
style_screen_contacts_icon_main_main_default.set_img_opa(0)

# add style for screen_Contacts_Icon
screen_Contacts_Icon.add_style(style_screen_contacts_icon_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_Call_Icon = lv.img(screen)
screen_Call_Icon.set_pos(176,189)
screen_Call_Icon.set_size(30,30)
screen_Call_Icon.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp700472752.png','rb') as f:
        screen_Call_Icon_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp700472752.png')
    sys.exit()

screen_Call_Icon_img = lv.img_dsc_t({
  'data_size': len(screen_Call_Icon_img_data),
  'header': {'always_zero': 0, 'w': 30, 'h': 30, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_Call_Icon_img_data
})

screen_Call_Icon.set_src(screen_Call_Icon_img)
screen_Call_Icon.set_pivot(0,0)
screen_Call_Icon.set_angle(0)
# create style style_screen_call_icon_main_main_default
style_screen_call_icon_main_main_default = lv.style_t()
style_screen_call_icon_main_main_default.init()
style_screen_call_icon_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_call_icon_main_main_default.set_img_recolor_opa(0)
style_screen_call_icon_main_main_default.set_img_opa(177)

# add style for screen_Call_Icon
screen_Call_Icon.add_style(style_screen_call_icon_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_Incoming_Call_Accept = lv.img(screen)
screen_Incoming_Call_Accept.set_pos(152,216)
screen_Incoming_Call_Accept.set_size(30,30)
screen_Incoming_Call_Accept.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1015655936.png','rb') as f:
        screen_Incoming_Call_Accept_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1015655936.png')
    sys.exit()

screen_Incoming_Call_Accept_img = lv.img_dsc_t({
  'data_size': len(screen_Incoming_Call_Accept_img_data),
  'header': {'always_zero': 0, 'w': 30, 'h': 30, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_Incoming_Call_Accept_img_data
})

screen_Incoming_Call_Accept.set_src(screen_Incoming_Call_Accept_img)
screen_Incoming_Call_Accept.set_pivot(0,0)
screen_Incoming_Call_Accept.set_angle(0)
# create style style_screen_incoming_call_accept_main_main_default
style_screen_incoming_call_accept_main_main_default = lv.style_t()
style_screen_incoming_call_accept_main_main_default.init()
style_screen_incoming_call_accept_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_incoming_call_accept_main_main_default.set_img_recolor_opa(0)
style_screen_incoming_call_accept_main_main_default.set_img_opa(255)

# add style for screen_Incoming_Call_Accept
screen_Incoming_Call_Accept.add_style(style_screen_incoming_call_accept_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_Incoming_Call_Decline = lv.img(screen)
screen_Incoming_Call_Decline.set_pos(58,216)
screen_Incoming_Call_Decline.set_size(30,30)
screen_Incoming_Call_Decline.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1989518958.png','rb') as f:
        screen_Incoming_Call_Decline_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1989518958.png')
    sys.exit()

screen_Incoming_Call_Decline_img = lv.img_dsc_t({
  'data_size': len(screen_Incoming_Call_Decline_img_data),
  'header': {'always_zero': 0, 'w': 30, 'h': 30, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_Incoming_Call_Decline_img_data
})

screen_Incoming_Call_Decline.set_src(screen_Incoming_Call_Decline_img)
screen_Incoming_Call_Decline.set_pivot(0,0)
screen_Incoming_Call_Decline.set_angle(0)
# create style style_screen_incoming_call_decline_main_main_default
style_screen_incoming_call_decline_main_main_default = lv.style_t()
style_screen_incoming_call_decline_main_main_default.init()
style_screen_incoming_call_decline_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_incoming_call_decline_main_main_default.set_img_recolor_opa(0)
style_screen_incoming_call_decline_main_main_default.set_img_opa(255)

# add style for screen_Incoming_Call_Decline
screen_Incoming_Call_Decline.add_style(style_screen_incoming_call_decline_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_Call_Decline = lv.img(screen)
screen_Call_Decline.set_pos(105,216)
screen_Call_Decline.set_size(30,30)
screen_Call_Decline.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp1501369258.png','rb') as f:
        screen_Call_Decline_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp1501369258.png')
    sys.exit()

screen_Call_Decline_img = lv.img_dsc_t({
  'data_size': len(screen_Call_Decline_img_data),
  'header': {'always_zero': 0, 'w': 30, 'h': 30, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_Call_Decline_img_data
})

screen_Call_Decline.set_src(screen_Call_Decline_img)
screen_Call_Decline.set_pivot(0,0)
screen_Call_Decline.set_angle(0)
# create style style_screen_call_decline_main_main_default
style_screen_call_decline_main_main_default = lv.style_t()
style_screen_call_decline_main_main_default.init()
style_screen_call_decline_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_call_decline_main_main_default.set_img_recolor_opa(0)
style_screen_call_decline_main_main_default.set_img_opa(255)

# add style for screen_Call_Decline
screen_Call_Decline.add_style(style_screen_call_decline_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_Mute_On = lv.img(screen)
screen_Mute_On.set_pos(152,216)
screen_Mute_On.set_size(30,31)
screen_Mute_On.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1072876611.png','rb') as f:
        screen_Mute_On_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1072876611.png')
    sys.exit()

screen_Mute_On_img = lv.img_dsc_t({
  'data_size': len(screen_Mute_On_img_data),
  'header': {'always_zero': 0, 'w': 30, 'h': 31, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_Mute_On_img_data
})

screen_Mute_On.set_src(screen_Mute_On_img)
screen_Mute_On.set_pivot(0,0)
screen_Mute_On.set_angle(0)
# create style style_screen_mute_on_main_main_default
style_screen_mute_on_main_main_default = lv.style_t()
style_screen_mute_on_main_main_default.init()
style_screen_mute_on_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_mute_on_main_main_default.set_img_recolor_opa(0)
style_screen_mute_on_main_main_default.set_img_opa(255)

# add style for screen_Mute_On
screen_Mute_On.add_style(style_screen_mute_on_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_Mute_Off = lv.img(screen)
screen_Mute_Off.set_pos(152,216)
screen_Mute_Off.set_size(30,31)
screen_Mute_Off.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-407772217.png','rb') as f:
        screen_Mute_Off_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-407772217.png')
    sys.exit()

screen_Mute_Off_img = lv.img_dsc_t({
  'data_size': len(screen_Mute_Off_img_data),
  'header': {'always_zero': 0, 'w': 30, 'h': 31, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_Mute_Off_img_data
})

screen_Mute_Off.set_src(screen_Mute_Off_img)
screen_Mute_Off.set_pivot(0,0)
screen_Mute_Off.set_angle(0)
# create style style_screen_mute_off_main_main_default
style_screen_mute_off_main_main_default = lv.style_t()
style_screen_mute_off_main_main_default.init()
style_screen_mute_off_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_mute_off_main_main_default.set_img_recolor_opa(0)
style_screen_mute_off_main_main_default.set_img_opa(255)

# add style for screen_Mute_Off
screen_Mute_Off.add_style(style_screen_mute_off_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_Night_Navigation_Icon = lv.img(screen)
screen_Night_Navigation_Icon.set_pos(105,252)
screen_Night_Navigation_Icon.set_size(30,30)
screen_Night_Navigation_Icon.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-2047171256.png','rb') as f:
        screen_Night_Navigation_Icon_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-2047171256.png')
    sys.exit()

screen_Night_Navigation_Icon_img = lv.img_dsc_t({
  'data_size': len(screen_Night_Navigation_Icon_img_data),
  'header': {'always_zero': 0, 'w': 30, 'h': 30, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_Night_Navigation_Icon_img_data
})

screen_Night_Navigation_Icon.set_src(screen_Night_Navigation_Icon_img)
screen_Night_Navigation_Icon.set_pivot(0,0)
screen_Night_Navigation_Icon.set_angle(0)
# create style style_screen_night_navigation_icon_main_main_default
style_screen_night_navigation_icon_main_main_default = lv.style_t()
style_screen_night_navigation_icon_main_main_default.init()
style_screen_night_navigation_icon_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_night_navigation_icon_main_main_default.set_img_recolor_opa(0)
style_screen_night_navigation_icon_main_main_default.set_img_opa(0)

# add style for screen_Night_Navigation_Icon
screen_Night_Navigation_Icon.add_style(style_screen_night_navigation_icon_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_Nav_Hour = lv.label(screen)
screen_Nav_Hour.set_pos(160,181)
screen_Nav_Hour.set_size(20,15)
screen_Nav_Hour.set_text("02")
screen_Nav_Hour.set_long_mode(lv.label.LONG.WRAP)
screen_Nav_Hour.set_style_text_align(lv.TEXT_ALIGN.CENTER, 0)
# create style style_screen_nav_hour_main_main_default
style_screen_nav_hour_main_main_default = lv.style_t()
style_screen_nav_hour_main_main_default.init()
style_screen_nav_hour_main_main_default.set_radius(0)
style_screen_nav_hour_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_screen_nav_hour_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_nav_hour_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_screen_nav_hour_main_main_default.set_bg_opa(0)
style_screen_nav_hour_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_screen_nav_hour_main_main_default.set_text_font(lv.font_FjallaOne_Regular_13)
except AttributeError:
    try:
        style_screen_nav_hour_main_main_default.set_text_font(lv.font_montserrat_13)
    except AttributeError:
        style_screen_nav_hour_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_nav_hour_main_main_default.set_text_letter_space(2)
style_screen_nav_hour_main_main_default.set_pad_left(0)
style_screen_nav_hour_main_main_default.set_pad_right(0)
style_screen_nav_hour_main_main_default.set_pad_top(0)
style_screen_nav_hour_main_main_default.set_pad_bottom(0)

# add style for screen_Nav_Hour
screen_Nav_Hour.add_style(style_screen_nav_hour_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_Nav_Colon = lv.label(screen)
screen_Nav_Colon.set_pos(175,179)
screen_Nav_Colon.set_size(15,15)
screen_Nav_Colon.set_text(":")
screen_Nav_Colon.set_long_mode(lv.label.LONG.WRAP)
screen_Nav_Colon.set_style_text_align(lv.TEXT_ALIGN.CENTER, 0)
# create style style_screen_nav_colon_main_main_default
style_screen_nav_colon_main_main_default = lv.style_t()
style_screen_nav_colon_main_main_default.init()
style_screen_nav_colon_main_main_default.set_radius(0)
style_screen_nav_colon_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_screen_nav_colon_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_nav_colon_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_screen_nav_colon_main_main_default.set_bg_opa(0)
style_screen_nav_colon_main_main_default.set_text_color(lv.color_make(0xf7,0xf7,0xf7))
try:
    style_screen_nav_colon_main_main_default.set_text_font(lv.font_FjallaOne_Regular_15)
except AttributeError:
    try:
        style_screen_nav_colon_main_main_default.set_text_font(lv.font_montserrat_15)
    except AttributeError:
        style_screen_nav_colon_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_nav_colon_main_main_default.set_text_letter_space(2)
style_screen_nav_colon_main_main_default.set_pad_left(0)
style_screen_nav_colon_main_main_default.set_pad_right(0)
style_screen_nav_colon_main_main_default.set_pad_top(0)
style_screen_nav_colon_main_main_default.set_pad_bottom(0)

# add style for screen_Nav_Colon
screen_Nav_Colon.add_style(style_screen_nav_colon_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_Nav_Minute = lv.label(screen)
screen_Nav_Minute.set_pos(184,180)
screen_Nav_Minute.set_size(20,15)
screen_Nav_Minute.set_text("00")
screen_Nav_Minute.set_long_mode(lv.label.LONG.WRAP)
screen_Nav_Minute.set_style_text_align(lv.TEXT_ALIGN.CENTER, 0)
# create style style_screen_nav_minute_main_main_default
style_screen_nav_minute_main_main_default = lv.style_t()
style_screen_nav_minute_main_main_default.init()
style_screen_nav_minute_main_main_default.set_radius(0)
style_screen_nav_minute_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_screen_nav_minute_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_nav_minute_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_screen_nav_minute_main_main_default.set_bg_opa(0)
style_screen_nav_minute_main_main_default.set_text_color(lv.color_make(0xfd,0xfc,0xfc))
try:
    style_screen_nav_minute_main_main_default.set_text_font(lv.font_FjallaOne_Regular_15)
except AttributeError:
    try:
        style_screen_nav_minute_main_main_default.set_text_font(lv.font_montserrat_15)
    except AttributeError:
        style_screen_nav_minute_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_nav_minute_main_main_default.set_text_letter_space(2)
style_screen_nav_minute_main_main_default.set_pad_left(0)
style_screen_nav_minute_main_main_default.set_pad_right(0)
style_screen_nav_minute_main_main_default.set_pad_top(0)
style_screen_nav_minute_main_main_default.set_pad_bottom(0)

# add style for screen_Nav_Minute
screen_Nav_Minute.add_style(style_screen_nav_minute_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_Nav_Am_Pm = lv.label(screen)
screen_Nav_Am_Pm.set_pos(200,181)
screen_Nav_Am_Pm.set_size(28,13)
screen_Nav_Am_Pm.set_text("AM")
screen_Nav_Am_Pm.set_long_mode(lv.label.LONG.WRAP)
screen_Nav_Am_Pm.set_style_text_align(lv.TEXT_ALIGN.CENTER, 0)
# create style style_screen_nav_am_pm_main_main_default
style_screen_nav_am_pm_main_main_default = lv.style_t()
style_screen_nav_am_pm_main_main_default.init()
style_screen_nav_am_pm_main_main_default.set_radius(0)
style_screen_nav_am_pm_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_screen_nav_am_pm_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_nav_am_pm_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_screen_nav_am_pm_main_main_default.set_bg_opa(255)
style_screen_nav_am_pm_main_main_default.set_text_color(lv.color_make(0x86,0x79,0x79))
try:
    style_screen_nav_am_pm_main_main_default.set_text_font(lv.font_FjallaOne_Regular_14)
except AttributeError:
    try:
        style_screen_nav_am_pm_main_main_default.set_text_font(lv.font_montserrat_14)
    except AttributeError:
        style_screen_nav_am_pm_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_nav_am_pm_main_main_default.set_text_letter_space(2)
style_screen_nav_am_pm_main_main_default.set_pad_left(0)
style_screen_nav_am_pm_main_main_default.set_pad_right(0)
style_screen_nav_am_pm_main_main_default.set_pad_top(0)
style_screen_nav_am_pm_main_main_default.set_pad_bottom(0)

# add style for screen_Nav_Am_Pm
screen_Nav_Am_Pm.add_style(style_screen_nav_am_pm_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_screen_nav_am_pm_main_main_disabled
style_screen_nav_am_pm_main_main_disabled = lv.style_t()
style_screen_nav_am_pm_main_main_disabled.init()
style_screen_nav_am_pm_main_main_disabled.set_radius(0)
style_screen_nav_am_pm_main_main_disabled.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_screen_nav_am_pm_main_main_disabled.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_nav_am_pm_main_main_disabled.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_screen_nav_am_pm_main_main_disabled.set_bg_opa(0)
style_screen_nav_am_pm_main_main_disabled.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_screen_nav_am_pm_main_main_disabled.set_text_font(lv.font_FjallaOne_Regular_12)
except AttributeError:
    try:
        style_screen_nav_am_pm_main_main_disabled.set_text_font(lv.font_montserrat_12)
    except AttributeError:
        style_screen_nav_am_pm_main_main_disabled.set_text_font(lv.font_montserrat_16)
style_screen_nav_am_pm_main_main_disabled.set_text_letter_space(2)
style_screen_nav_am_pm_main_main_disabled.set_pad_left(0)
style_screen_nav_am_pm_main_main_disabled.set_pad_right(0)
style_screen_nav_am_pm_main_main_disabled.set_pad_top(0)
style_screen_nav_am_pm_main_main_disabled.set_pad_bottom(0)

# add style for screen_Nav_Am_Pm
screen_Nav_Am_Pm.add_style(style_screen_nav_am_pm_main_main_disabled, lv.PART.MAIN|lv.STATE.DISABLED)

screen_Distance_Unit = lv.label(screen)
screen_Distance_Unit.set_pos(61,206)
screen_Distance_Unit.set_size(21,13)
screen_Distance_Unit.set_text("km")
screen_Distance_Unit.set_long_mode(lv.label.LONG.WRAP)
screen_Distance_Unit.set_style_text_align(lv.TEXT_ALIGN.CENTER, 0)
# create style style_screen_distance_unit_main_main_default
style_screen_distance_unit_main_main_default = lv.style_t()
style_screen_distance_unit_main_main_default.init()
style_screen_distance_unit_main_main_default.set_radius(0)
style_screen_distance_unit_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_screen_distance_unit_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_distance_unit_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_screen_distance_unit_main_main_default.set_bg_opa(0)
style_screen_distance_unit_main_main_default.set_text_color(lv.color_make(0xf2,0x70,0x08))
try:
    style_screen_distance_unit_main_main_default.set_text_font(lv.font_FjallaOne_Regular_13)
except AttributeError:
    try:
        style_screen_distance_unit_main_main_default.set_text_font(lv.font_montserrat_13)
    except AttributeError:
        style_screen_distance_unit_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_distance_unit_main_main_default.set_text_letter_space(2)
style_screen_distance_unit_main_main_default.set_pad_left(0)
style_screen_distance_unit_main_main_default.set_pad_right(0)
style_screen_distance_unit_main_main_default.set_pad_top(0)
style_screen_distance_unit_main_main_default.set_pad_bottom(0)

# add style for screen_Distance_Unit
screen_Distance_Unit.add_style(style_screen_distance_unit_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_Distance_Value = lv.label(screen)
screen_Distance_Value.set_pos(50,180)
screen_Distance_Value.set_size(32,18)
screen_Distance_Value.set_text("999")
screen_Distance_Value.set_long_mode(lv.label.LONG.WRAP)
screen_Distance_Value.set_style_text_align(lv.TEXT_ALIGN.CENTER, 0)
# create style style_screen_distance_value_main_main_default
style_screen_distance_value_main_main_default = lv.style_t()
style_screen_distance_value_main_main_default.init()
style_screen_distance_value_main_main_default.set_radius(0)
style_screen_distance_value_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_screen_distance_value_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_distance_value_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_screen_distance_value_main_main_default.set_bg_opa(0)
style_screen_distance_value_main_main_default.set_text_color(lv.color_make(0xf7,0x70,0x08))
try:
    style_screen_distance_value_main_main_default.set_text_font(lv.font_FjallaOne_Regular_14)
except AttributeError:
    try:
        style_screen_distance_value_main_main_default.set_text_font(lv.font_montserrat_14)
    except AttributeError:
        style_screen_distance_value_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_distance_value_main_main_default.set_text_letter_space(2)
style_screen_distance_value_main_main_default.set_pad_left(0)
style_screen_distance_value_main_main_default.set_pad_right(0)
style_screen_distance_value_main_main_default.set_pad_top(0)
style_screen_distance_value_main_main_default.set_pad_bottom(0)

# add style for screen_Distance_Value
screen_Distance_Value.add_style(style_screen_distance_value_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_Night_ETA = lv.label(screen)
screen_Night_ETA.set_pos(173,204)
screen_Night_ETA.set_size(26,14)
screen_Night_ETA.set_text("ETA")
screen_Night_ETA.set_long_mode(lv.label.LONG.WRAP)
screen_Night_ETA.set_style_text_align(lv.TEXT_ALIGN.CENTER, 0)
# create style style_screen_night_eta_main_main_default
style_screen_night_eta_main_main_default = lv.style_t()
style_screen_night_eta_main_main_default.init()
style_screen_night_eta_main_main_default.set_radius(0)
style_screen_night_eta_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_screen_night_eta_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_night_eta_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_screen_night_eta_main_main_default.set_bg_opa(0)
style_screen_night_eta_main_main_default.set_text_color(lv.color_make(0x86,0x79,0x79))
try:
    style_screen_night_eta_main_main_default.set_text_font(lv.font_FjallaOne_Regular_1)
except AttributeError:
    try:
        style_screen_night_eta_main_main_default.set_text_font(lv.font_montserrat_1)
    except AttributeError:
        style_screen_night_eta_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_night_eta_main_main_default.set_text_letter_space(2)
style_screen_night_eta_main_main_default.set_pad_left(0)
style_screen_night_eta_main_main_default.set_pad_right(0)
style_screen_night_eta_main_main_default.set_pad_top(0)
style_screen_night_eta_main_main_default.set_pad_bottom(0)

# add style for screen_Night_ETA
screen_Night_ETA.add_style(style_screen_night_eta_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_Destination_Reached = lv.img(screen)
screen_Destination_Reached.set_pos(102,191)
screen_Destination_Reached.set_size(36,48)
screen_Destination_Reached.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-2066180014.png','rb') as f:
        screen_Destination_Reached_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-2066180014.png')
    sys.exit()

screen_Destination_Reached_img = lv.img_dsc_t({
  'data_size': len(screen_Destination_Reached_img_data),
  'header': {'always_zero': 0, 'w': 36, 'h': 48, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_Destination_Reached_img_data
})

screen_Destination_Reached.set_src(screen_Destination_Reached_img)
screen_Destination_Reached.set_pivot(0,0)
screen_Destination_Reached.set_angle(0)
# create style style_screen_destination_reached_main_main_default
style_screen_destination_reached_main_main_default = lv.style_t()
style_screen_destination_reached_main_main_default.init()
style_screen_destination_reached_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_destination_reached_main_main_default.set_img_recolor_opa(0)
style_screen_destination_reached_main_main_default.set_img_opa(0)

# add style for screen_Destination_Reached
screen_Destination_Reached.add_style(style_screen_destination_reached_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_Night_Ferry_Train = lv.img(screen)
screen_Night_Ferry_Train.set_pos(94,197)
screen_Night_Ferry_Train.set_size(52,40)
screen_Night_Ferry_Train.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp1466002054.png','rb') as f:
        screen_Night_Ferry_Train_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp1466002054.png')
    sys.exit()

screen_Night_Ferry_Train_img = lv.img_dsc_t({
  'data_size': len(screen_Night_Ferry_Train_img_data),
  'header': {'always_zero': 0, 'w': 52, 'h': 40, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_Night_Ferry_Train_img_data
})

screen_Night_Ferry_Train.set_src(screen_Night_Ferry_Train_img)
screen_Night_Ferry_Train.set_pivot(0,0)
screen_Night_Ferry_Train.set_angle(0)
# create style style_screen_night_ferry_train_main_main_default
style_screen_night_ferry_train_main_main_default = lv.style_t()
style_screen_night_ferry_train_main_main_default.init()
style_screen_night_ferry_train_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_night_ferry_train_main_main_default.set_img_recolor_opa(0)
style_screen_night_ferry_train_main_main_default.set_img_opa(0)

# add style for screen_Night_Ferry_Train
screen_Night_Ferry_Train.add_style(style_screen_night_ferry_train_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_Night_Ferry = lv.img(screen)
screen_Night_Ferry.set_pos(93,190)
screen_Night_Ferry.set_size(54,47)
screen_Night_Ferry.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1752011514.png','rb') as f:
        screen_Night_Ferry_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1752011514.png')
    sys.exit()

screen_Night_Ferry_img = lv.img_dsc_t({
  'data_size': len(screen_Night_Ferry_img_data),
  'header': {'always_zero': 0, 'w': 54, 'h': 47, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_Night_Ferry_img_data
})

screen_Night_Ferry.set_src(screen_Night_Ferry_img)
screen_Night_Ferry.set_pivot(0,0)
screen_Night_Ferry.set_angle(0)
# create style style_screen_night_ferry_main_main_default
style_screen_night_ferry_main_main_default = lv.style_t()
style_screen_night_ferry_main_main_default.init()
style_screen_night_ferry_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_night_ferry_main_main_default.set_img_recolor_opa(0)
style_screen_night_ferry_main_main_default.set_img_opa(0)

# add style for screen_Night_Ferry
screen_Night_Ferry.add_style(style_screen_night_ferry_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_Night_Fork_left = lv.img(screen)
screen_Night_Fork_left.set_pos(85,183)
screen_Night_Fork_left.set_size(61,65)
screen_Night_Fork_left.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp497794984.png','rb') as f:
        screen_Night_Fork_left_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp497794984.png')
    sys.exit()

screen_Night_Fork_left_img = lv.img_dsc_t({
  'data_size': len(screen_Night_Fork_left_img_data),
  'header': {'always_zero': 0, 'w': 61, 'h': 65, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_Night_Fork_left_img_data
})

screen_Night_Fork_left.set_src(screen_Night_Fork_left_img)
screen_Night_Fork_left.set_pivot(0,0)
screen_Night_Fork_left.set_angle(0)
# create style style_screen_night_fork_left_main_main_default
style_screen_night_fork_left_main_main_default = lv.style_t()
style_screen_night_fork_left_main_main_default.init()
style_screen_night_fork_left_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_night_fork_left_main_main_default.set_img_recolor_opa(0)
style_screen_night_fork_left_main_main_default.set_img_opa(0)

# add style for screen_Night_Fork_left
screen_Night_Fork_left.add_style(style_screen_night_fork_left_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_Night_Fork_Right = lv.img(screen)
screen_Night_Fork_Right.set_pos(94,183)
screen_Night_Fork_Right.set_size(61,65)
screen_Night_Fork_Right.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-237902161.png','rb') as f:
        screen_Night_Fork_Right_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-237902161.png')
    sys.exit()

screen_Night_Fork_Right_img = lv.img_dsc_t({
  'data_size': len(screen_Night_Fork_Right_img_data),
  'header': {'always_zero': 0, 'w': 61, 'h': 65, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_Night_Fork_Right_img_data
})

screen_Night_Fork_Right.set_src(screen_Night_Fork_Right_img)
screen_Night_Fork_Right.set_pivot(0,0)
screen_Night_Fork_Right.set_angle(0)
# create style style_screen_night_fork_right_main_main_default
style_screen_night_fork_right_main_main_default = lv.style_t()
style_screen_night_fork_right_main_main_default.init()
style_screen_night_fork_right_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_night_fork_right_main_main_default.set_img_recolor_opa(0)
style_screen_night_fork_right_main_main_default.set_img_opa(0)

# add style for screen_Night_Fork_Right
screen_Night_Fork_Right.add_style(style_screen_night_fork_right_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_Night_Keep_Left = lv.img(screen)
screen_Night_Keep_Left.set_pos(85,183)
screen_Night_Keep_Left.set_size(61,65)
screen_Night_Keep_Left.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp881662917.png','rb') as f:
        screen_Night_Keep_Left_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp881662917.png')
    sys.exit()

screen_Night_Keep_Left_img = lv.img_dsc_t({
  'data_size': len(screen_Night_Keep_Left_img_data),
  'header': {'always_zero': 0, 'w': 61, 'h': 65, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_Night_Keep_Left_img_data
})

screen_Night_Keep_Left.set_src(screen_Night_Keep_Left_img)
screen_Night_Keep_Left.set_pivot(0,0)
screen_Night_Keep_Left.set_angle(0)
# create style style_screen_night_keep_left_main_main_default
style_screen_night_keep_left_main_main_default = lv.style_t()
style_screen_night_keep_left_main_main_default.init()
style_screen_night_keep_left_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_night_keep_left_main_main_default.set_img_recolor_opa(0)
style_screen_night_keep_left_main_main_default.set_img_opa(0)

# add style for screen_Night_Keep_Left
screen_Night_Keep_Left.add_style(style_screen_night_keep_left_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_NIght_Keep_Right = lv.img(screen)
screen_NIght_Keep_Right.set_pos(94,183)
screen_NIght_Keep_Right.set_size(61,65)
screen_NIght_Keep_Right.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-237902161.png','rb') as f:
        screen_NIght_Keep_Right_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-237902161.png')
    sys.exit()

screen_NIght_Keep_Right_img = lv.img_dsc_t({
  'data_size': len(screen_NIght_Keep_Right_img_data),
  'header': {'always_zero': 0, 'w': 61, 'h': 65, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_NIght_Keep_Right_img_data
})

screen_NIght_Keep_Right.set_src(screen_NIght_Keep_Right_img)
screen_NIght_Keep_Right.set_pivot(0,0)
screen_NIght_Keep_Right.set_angle(0)
# create style style_screen_night_keep_right_main_main_default
style_screen_night_keep_right_main_main_default = lv.style_t()
style_screen_night_keep_right_main_main_default.init()
style_screen_night_keep_right_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_night_keep_right_main_main_default.set_img_recolor_opa(0)
style_screen_night_keep_right_main_main_default.set_img_opa(3)

# add style for screen_NIght_Keep_Right
screen_NIght_Keep_Right.add_style(style_screen_night_keep_right_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_NIght_Merge = lv.img(screen)
screen_NIght_Merge.set_pos(101,182)
screen_NIght_Merge.set_size(39,66)
screen_NIght_Merge.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1104201624.png','rb') as f:
        screen_NIght_Merge_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1104201624.png')
    sys.exit()

screen_NIght_Merge_img = lv.img_dsc_t({
  'data_size': len(screen_NIght_Merge_img_data),
  'header': {'always_zero': 0, 'w': 39, 'h': 66, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_NIght_Merge_img_data
})

screen_NIght_Merge.set_src(screen_NIght_Merge_img)
screen_NIght_Merge.set_pivot(0,0)
screen_NIght_Merge.set_angle(0)
# create style style_screen_night_merge_main_main_default
style_screen_night_merge_main_main_default = lv.style_t()
style_screen_night_merge_main_main_default.init()
style_screen_night_merge_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_night_merge_main_main_default.set_img_recolor_opa(0)
style_screen_night_merge_main_main_default.set_img_opa(0)

# add style for screen_NIght_Merge
screen_NIght_Merge.add_style(style_screen_night_merge_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_Night_Straight = lv.img(screen)
screen_Night_Straight.set_pos(105,180)
screen_Night_Straight.set_size(32,68)
screen_Night_Straight.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp55468657.png','rb') as f:
        screen_Night_Straight_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp55468657.png')
    sys.exit()

screen_Night_Straight_img = lv.img_dsc_t({
  'data_size': len(screen_Night_Straight_img_data),
  'header': {'always_zero': 0, 'w': 32, 'h': 68, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_Night_Straight_img_data
})

screen_Night_Straight.set_src(screen_Night_Straight_img)
screen_Night_Straight.set_pivot(0,0)
screen_Night_Straight.set_angle(0)
# create style style_screen_night_straight_main_main_default
style_screen_night_straight_main_main_default = lv.style_t()
style_screen_night_straight_main_main_default.init()
style_screen_night_straight_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_night_straight_main_main_default.set_img_recolor_opa(0)
style_screen_night_straight_main_main_default.set_img_opa(0)

# add style for screen_Night_Straight
screen_Night_Straight.add_style(style_screen_night_straight_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_Nt_Turn_Sharp_Left = lv.img(screen)
screen_Nt_Turn_Sharp_Left.set_pos(87,178)
screen_Nt_Turn_Sharp_Left.set_size(38,70)
screen_Nt_Turn_Sharp_Left.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-936782266.png','rb') as f:
        screen_Nt_Turn_Sharp_Left_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-936782266.png')
    sys.exit()

screen_Nt_Turn_Sharp_Left_img = lv.img_dsc_t({
  'data_size': len(screen_Nt_Turn_Sharp_Left_img_data),
  'header': {'always_zero': 0, 'w': 38, 'h': 70, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_Nt_Turn_Sharp_Left_img_data
})

screen_Nt_Turn_Sharp_Left.set_src(screen_Nt_Turn_Sharp_Left_img)
screen_Nt_Turn_Sharp_Left.set_pivot(0,0)
screen_Nt_Turn_Sharp_Left.set_angle(0)
# create style style_screen_nt_turn_sharp_left_main_main_default
style_screen_nt_turn_sharp_left_main_main_default = lv.style_t()
style_screen_nt_turn_sharp_left_main_main_default.init()
style_screen_nt_turn_sharp_left_main_main_default.set_img_recolor(lv.color_make(0x08,0x08,0x08))
style_screen_nt_turn_sharp_left_main_main_default.set_img_recolor_opa(0)
style_screen_nt_turn_sharp_left_main_main_default.set_img_opa(0)

# add style for screen_Nt_Turn_Sharp_Left
screen_Nt_Turn_Sharp_Left.add_style(style_screen_nt_turn_sharp_left_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_D_1 = lv.img(screen)
screen_D_1.set_pos(57,124)
screen_D_1.set_size(39,69)
screen_D_1.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp461390365.png','rb') as f:
        screen_D_1_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp461390365.png')
    sys.exit()

screen_D_1_img = lv.img_dsc_t({
  'data_size': len(screen_D_1_img_data),
  'header': {'always_zero': 0, 'w': 39, 'h': 69, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_D_1_img_data
})

screen_D_1.set_src(screen_D_1_img)
screen_D_1.set_pivot(0,0)
screen_D_1.set_angle(0)
# create style style_screen_d_1_main_main_default
style_screen_d_1_main_main_default = lv.style_t()
style_screen_d_1_main_main_default.init()
style_screen_d_1_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_d_1_main_main_default.set_img_recolor_opa(0)
style_screen_d_1_main_main_default.set_img_opa(0)

# add style for screen_D_1
screen_D_1.add_style(style_screen_d_1_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_D_2 = lv.img(screen)
screen_D_2.set_pos(57,124)
screen_D_2.set_size(39,69)
screen_D_2.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1615818978.png','rb') as f:
        screen_D_2_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1615818978.png')
    sys.exit()

screen_D_2_img = lv.img_dsc_t({
  'data_size': len(screen_D_2_img_data),
  'header': {'always_zero': 0, 'w': 39, 'h': 69, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_D_2_img_data
})

screen_D_2.set_src(screen_D_2_img)
screen_D_2.set_pivot(0,0)
screen_D_2.set_angle(0)
# create style style_screen_d_2_main_main_default
style_screen_d_2_main_main_default = lv.style_t()
style_screen_d_2_main_main_default.init()
style_screen_d_2_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_d_2_main_main_default.set_img_recolor_opa(0)
style_screen_d_2_main_main_default.set_img_opa(0)

# add style for screen_D_2
screen_D_2.add_style(style_screen_d_2_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_D_3 = lv.img(screen)
screen_D_3.set_pos(57,124)
screen_D_3.set_size(39,69)
screen_D_3.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp601938975.png','rb') as f:
        screen_D_3_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp601938975.png')
    sys.exit()

screen_D_3_img = lv.img_dsc_t({
  'data_size': len(screen_D_3_img_data),
  'header': {'always_zero': 0, 'w': 39, 'h': 69, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_D_3_img_data
})

screen_D_3.set_src(screen_D_3_img)
screen_D_3.set_pivot(0,0)
screen_D_3.set_angle(0)
# create style style_screen_d_3_main_main_default
style_screen_d_3_main_main_default = lv.style_t()
style_screen_d_3_main_main_default.init()
style_screen_d_3_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_d_3_main_main_default.set_img_recolor_opa(0)
style_screen_d_3_main_main_default.set_img_opa(0)

# add style for screen_D_3
screen_D_3.add_style(style_screen_d_3_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_D_4 = lv.img(screen)
screen_D_4.set_pos(57,124)
screen_D_4.set_size(39,69)
screen_D_4.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1475270368.png','rb') as f:
        screen_D_4_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1475270368.png')
    sys.exit()

screen_D_4_img = lv.img_dsc_t({
  'data_size': len(screen_D_4_img_data),
  'header': {'always_zero': 0, 'w': 39, 'h': 69, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_D_4_img_data
})

screen_D_4.set_src(screen_D_4_img)
screen_D_4.set_pivot(0,0)
screen_D_4.set_angle(0)
# create style style_screen_d_4_main_main_default
style_screen_d_4_main_main_default = lv.style_t()
style_screen_d_4_main_main_default.init()
style_screen_d_4_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_d_4_main_main_default.set_img_recolor_opa(0)
style_screen_d_4_main_main_default.set_img_opa(0)

# add style for screen_D_4
screen_D_4.add_style(style_screen_d_4_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_D_5 = lv.img(screen)
screen_D_5.set_pos(57,124)
screen_D_5.set_size(39,69)
screen_D_5.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp742487585.png','rb') as f:
        screen_D_5_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp742487585.png')
    sys.exit()

screen_D_5_img = lv.img_dsc_t({
  'data_size': len(screen_D_5_img_data),
  'header': {'always_zero': 0, 'w': 39, 'h': 69, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_D_5_img_data
})

screen_D_5.set_src(screen_D_5_img)
screen_D_5.set_pivot(0,0)
screen_D_5.set_angle(0)
# create style style_screen_d_5_main_main_default
style_screen_d_5_main_main_default = lv.style_t()
style_screen_d_5_main_main_default.init()
style_screen_d_5_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_d_5_main_main_default.set_img_recolor_opa(0)
style_screen_d_5_main_main_default.set_img_opa(0)

# add style for screen_D_5
screen_D_5.add_style(style_screen_d_5_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_D_6 = lv.img(screen)
screen_D_6.set_pos(57,124)
screen_D_6.set_size(39,69)
screen_D_6.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1334721758.png','rb') as f:
        screen_D_6_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1334721758.png')
    sys.exit()

screen_D_6_img = lv.img_dsc_t({
  'data_size': len(screen_D_6_img_data),
  'header': {'always_zero': 0, 'w': 39, 'h': 69, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_D_6_img_data
})

screen_D_6.set_src(screen_D_6_img)
screen_D_6.set_pivot(0,0)
screen_D_6.set_angle(0)
# create style style_screen_d_6_main_main_default
style_screen_d_6_main_main_default = lv.style_t()
style_screen_d_6_main_main_default.init()
style_screen_d_6_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_d_6_main_main_default.set_img_recolor_opa(0)
style_screen_d_6_main_main_default.set_img_opa(0)

# add style for screen_D_6
screen_D_6.add_style(style_screen_d_6_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_D_7 = lv.img(screen)
screen_D_7.set_pos(57,124)
screen_D_7.set_size(39,69)
screen_D_7.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp883036195.png','rb') as f:
        screen_D_7_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp883036195.png')
    sys.exit()

screen_D_7_img = lv.img_dsc_t({
  'data_size': len(screen_D_7_img_data),
  'header': {'always_zero': 0, 'w': 39, 'h': 69, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_D_7_img_data
})

screen_D_7.set_src(screen_D_7_img)
screen_D_7.set_pivot(0,0)
screen_D_7.set_angle(0)
# create style style_screen_d_7_main_main_default
style_screen_d_7_main_main_default = lv.style_t()
style_screen_d_7_main_main_default.init()
style_screen_d_7_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_d_7_main_main_default.set_img_recolor_opa(0)
style_screen_d_7_main_main_default.set_img_opa(0)

# add style for screen_D_7
screen_D_7.add_style(style_screen_d_7_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_D_8 = lv.img(screen)
screen_D_8.set_pos(57,124)
screen_D_8.set_size(39,69)
screen_D_8.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1194173148.png','rb') as f:
        screen_D_8_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1194173148.png')
    sys.exit()

screen_D_8_img = lv.img_dsc_t({
  'data_size': len(screen_D_8_img_data),
  'header': {'always_zero': 0, 'w': 39, 'h': 69, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_D_8_img_data
})

screen_D_8.set_src(screen_D_8_img)
screen_D_8.set_pivot(0,0)
screen_D_8.set_angle(0)
# create style style_screen_d_8_main_main_default
style_screen_d_8_main_main_default = lv.style_t()
style_screen_d_8_main_main_default.init()
style_screen_d_8_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_d_8_main_main_default.set_img_recolor_opa(0)
style_screen_d_8_main_main_default.set_img_opa(0)

# add style for screen_D_8
screen_D_8.add_style(style_screen_d_8_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_D_9 = lv.img(screen)
screen_D_9.set_pos(57,124)
screen_D_9.set_size(39,69)
screen_D_9.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp1023584805.png','rb') as f:
        screen_D_9_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp1023584805.png')
    sys.exit()

screen_D_9_img = lv.img_dsc_t({
  'data_size': len(screen_D_9_img_data),
  'header': {'always_zero': 0, 'w': 39, 'h': 69, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_D_9_img_data
})

screen_D_9.set_src(screen_D_9_img)
screen_D_9.set_pivot(0,0)
screen_D_9.set_angle(0)
# create style style_screen_d_9_main_main_default
style_screen_d_9_main_main_default = lv.style_t()
style_screen_d_9_main_main_default.init()
style_screen_d_9_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_d_9_main_main_default.set_img_recolor_opa(0)
style_screen_d_9_main_main_default.set_img_opa(0)

# add style for screen_D_9
screen_D_9.add_style(style_screen_d_9_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_D_10 = lv.img(screen)
screen_D_10.set_pos(100,124)
screen_D_10.set_size(36,74)
screen_D_10.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp1789809967.png','rb') as f:
        screen_D_10_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp1789809967.png')
    sys.exit()

screen_D_10_img = lv.img_dsc_t({
  'data_size': len(screen_D_10_img_data),
  'header': {'always_zero': 0, 'w': 36, 'h': 74, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_D_10_img_data
})

screen_D_10.set_src(screen_D_10_img)
screen_D_10.set_pivot(0,0)
screen_D_10.set_angle(0)
# create style style_screen_d_10_main_main_default
style_screen_d_10_main_main_default = lv.style_t()
style_screen_d_10_main_main_default.init()
style_screen_d_10_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_d_10_main_main_default.set_img_recolor_opa(0)
style_screen_d_10_main_main_default.set_img_opa(0)

# add style for screen_D_10
screen_D_10.add_style(style_screen_d_10_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_D_11 = lv.img(screen)
screen_D_11.set_pos(100,124)
screen_D_11.set_size(36,74)
screen_D_11.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp321650050.png','rb') as f:
        screen_D_11_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp321650050.png')
    sys.exit()

screen_D_11_img = lv.img_dsc_t({
  'data_size': len(screen_D_11_img_data),
  'header': {'always_zero': 0, 'w': 36, 'h': 74, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_D_11_img_data
})

screen_D_11.set_src(screen_D_11_img)
screen_D_11.set_pivot(0,0)
screen_D_11.set_angle(0)
# create style style_screen_d_11_main_main_default
style_screen_d_11_main_main_default = lv.style_t()
style_screen_d_11_main_main_default.init()
style_screen_d_11_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_d_11_main_main_default.set_img_recolor_opa(0)
style_screen_d_11_main_main_default.set_img_opa(0)

# add style for screen_D_11
screen_D_11.add_style(style_screen_d_11_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_D_12 = lv.img(screen)
screen_D_12.set_pos(100,124)
screen_D_12.set_size(36,74)
screen_D_12.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1755559293.png','rb') as f:
        screen_D_12_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1755559293.png')
    sys.exit()

screen_D_12_img = lv.img_dsc_t({
  'data_size': len(screen_D_12_img_data),
  'header': {'always_zero': 0, 'w': 36, 'h': 74, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_D_12_img_data
})

screen_D_12.set_src(screen_D_12_img)
screen_D_12.set_pivot(0,0)
screen_D_12.set_angle(0)
# create style style_screen_d_12_main_main_default
style_screen_d_12_main_main_default = lv.style_t()
style_screen_d_12_main_main_default.init()
style_screen_d_12_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_d_12_main_main_default.set_img_recolor_opa(0)
style_screen_d_12_main_main_default.set_img_opa(0)

# add style for screen_D_12
screen_D_12.add_style(style_screen_d_12_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_D_13 = lv.img(screen)
screen_D_13.set_pos(100,124)
screen_D_13.set_size(36,74)
screen_D_13.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp462198660.png','rb') as f:
        screen_D_13_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp462198660.png')
    sys.exit()

screen_D_13_img = lv.img_dsc_t({
  'data_size': len(screen_D_13_img_data),
  'header': {'always_zero': 0, 'w': 36, 'h': 74, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_D_13_img_data
})

screen_D_13.set_src(screen_D_13_img)
screen_D_13.set_pivot(0,0)
screen_D_13.set_angle(0)
# create style style_screen_d_13_main_main_default
style_screen_d_13_main_main_default = lv.style_t()
style_screen_d_13_main_main_default.init()
style_screen_d_13_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_d_13_main_main_default.set_img_recolor_opa(0)
style_screen_d_13_main_main_default.set_img_opa(0)

# add style for screen_D_13
screen_D_13.add_style(style_screen_d_13_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_D_14 = lv.img(screen)
screen_D_14.set_pos(100,124)
screen_D_14.set_size(36,74)
screen_D_14.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1615010683.png','rb') as f:
        screen_D_14_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1615010683.png')
    sys.exit()

screen_D_14_img = lv.img_dsc_t({
  'data_size': len(screen_D_14_img_data),
  'header': {'always_zero': 0, 'w': 36, 'h': 74, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_D_14_img_data
})

screen_D_14.set_src(screen_D_14_img)
screen_D_14.set_pivot(0,0)
screen_D_14.set_angle(0)
# create style style_screen_d_14_main_main_default
style_screen_d_14_main_main_default = lv.style_t()
style_screen_d_14_main_main_default.init()
style_screen_d_14_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_d_14_main_main_default.set_img_recolor_opa(0)
style_screen_d_14_main_main_default.set_img_opa(0)

# add style for screen_D_14
screen_D_14.add_style(style_screen_d_14_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_D_15 = lv.img(screen)
screen_D_15.set_pos(100,124)
screen_D_15.set_size(36,74)
screen_D_15.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp602747270.png','rb') as f:
        screen_D_15_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp602747270.png')
    sys.exit()

screen_D_15_img = lv.img_dsc_t({
  'data_size': len(screen_D_15_img_data),
  'header': {'always_zero': 0, 'w': 36, 'h': 74, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_D_15_img_data
})

screen_D_15.set_src(screen_D_15_img)
screen_D_15.set_pivot(0,0)
screen_D_15.set_angle(0)
# create style style_screen_d_15_main_main_default
style_screen_d_15_main_main_default = lv.style_t()
style_screen_d_15_main_main_default.init()
style_screen_d_15_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_d_15_main_main_default.set_img_recolor_opa(0)
style_screen_d_15_main_main_default.set_img_opa(0)

# add style for screen_D_15
screen_D_15.add_style(style_screen_d_15_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_D_16 = lv.img(screen)
screen_D_16.set_pos(100,124)
screen_D_16.set_size(36,74)
screen_D_16.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1474462073.png','rb') as f:
        screen_D_16_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1474462073.png')
    sys.exit()

screen_D_16_img = lv.img_dsc_t({
  'data_size': len(screen_D_16_img_data),
  'header': {'always_zero': 0, 'w': 36, 'h': 74, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_D_16_img_data
})

screen_D_16.set_src(screen_D_16_img)
screen_D_16.set_pivot(0,0)
screen_D_16.set_angle(0)
# create style style_screen_d_16_main_main_default
style_screen_d_16_main_main_default = lv.style_t()
style_screen_d_16_main_main_default.init()
style_screen_d_16_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_d_16_main_main_default.set_img_recolor_opa(0)
style_screen_d_16_main_main_default.set_img_opa(0)

# add style for screen_D_16
screen_D_16.add_style(style_screen_d_16_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_D_17 = lv.img(screen)
screen_D_17.set_pos(100,124)
screen_D_17.set_size(36,74)
screen_D_17.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp743295880.png','rb') as f:
        screen_D_17_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp743295880.png')
    sys.exit()

screen_D_17_img = lv.img_dsc_t({
  'data_size': len(screen_D_17_img_data),
  'header': {'always_zero': 0, 'w': 36, 'h': 74, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_D_17_img_data
})

screen_D_17.set_src(screen_D_17_img)
screen_D_17.set_pivot(0,0)
screen_D_17.set_angle(0)
# create style style_screen_d_17_main_main_default
style_screen_d_17_main_main_default = lv.style_t()
style_screen_d_17_main_main_default.init()
style_screen_d_17_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_d_17_main_main_default.set_img_recolor_opa(0)
style_screen_d_17_main_main_default.set_img_opa(0)

# add style for screen_D_17
screen_D_17.add_style(style_screen_d_17_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_D_18 = lv.img(screen)
screen_D_18.set_pos(100,124)
screen_D_18.set_size(36,74)
screen_D_18.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1333913463.png','rb') as f:
        screen_D_18_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1333913463.png')
    sys.exit()

screen_D_18_img = lv.img_dsc_t({
  'data_size': len(screen_D_18_img_data),
  'header': {'always_zero': 0, 'w': 36, 'h': 74, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_D_18_img_data
})

screen_D_18.set_src(screen_D_18_img)
screen_D_18.set_pivot(0,0)
screen_D_18.set_angle(0)
# create style style_screen_d_18_main_main_default
style_screen_d_18_main_main_default = lv.style_t()
style_screen_d_18_main_main_default.init()
style_screen_d_18_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_d_18_main_main_default.set_img_recolor_opa(0)
style_screen_d_18_main_main_default.set_img_opa(0)

# add style for screen_D_18
screen_D_18.add_style(style_screen_d_18_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_D_19 = lv.img(screen)
screen_D_19.set_pos(145,124)
screen_D_19.set_size(36,74)
screen_D_19.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp883844490.png','rb') as f:
        screen_D_19_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp883844490.png')
    sys.exit()

screen_D_19_img = lv.img_dsc_t({
  'data_size': len(screen_D_19_img_data),
  'header': {'always_zero': 0, 'w': 36, 'h': 74, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_D_19_img_data
})

screen_D_19.set_src(screen_D_19_img)
screen_D_19.set_pivot(0,0)
screen_D_19.set_angle(0)
# create style style_screen_d_19_main_main_default
style_screen_d_19_main_main_default = lv.style_t()
style_screen_d_19_main_main_default.init()
style_screen_d_19_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_d_19_main_main_default.set_img_recolor_opa(0)
style_screen_d_19_main_main_default.set_img_opa(0)

# add style for screen_D_19
screen_D_19.add_style(style_screen_d_19_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_DI_20 = lv.img(screen)
screen_DI_20.set_pos(145,124)
screen_DI_20.set_size(36,74)
screen_DI_20.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-2013182283.png','rb') as f:
        screen_DI_20_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-2013182283.png')
    sys.exit()

screen_DI_20_img = lv.img_dsc_t({
  'data_size': len(screen_DI_20_img_data),
  'header': {'always_zero': 0, 'w': 36, 'h': 74, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_DI_20_img_data
})

screen_DI_20.set_src(screen_DI_20_img)
screen_DI_20.set_pivot(0,0)
screen_DI_20.set_angle(0)
# create style style_screen_di_20_main_main_default
style_screen_di_20_main_main_default = lv.style_t()
style_screen_di_20_main_main_default.init()
style_screen_di_20_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_di_20_main_main_default.set_img_recolor_opa(0)
style_screen_di_20_main_main_default.set_img_opa(0)

# add style for screen_DI_20
screen_DI_20.add_style(style_screen_di_20_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_DI_21 = lv.img(screen)
screen_DI_21.set_pos(145,124)
screen_DI_21.set_size(36,74)
screen_DI_21.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1606992708.png','rb') as f:
        screen_DI_21_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1606992708.png')
    sys.exit()

screen_DI_21_img = lv.img_dsc_t({
  'data_size': len(screen_DI_21_img_data),
  'header': {'always_zero': 0, 'w': 36, 'h': 74, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_DI_21_img_data
})

screen_DI_21.set_src(screen_DI_21_img)
screen_DI_21.set_pivot(0,0)
screen_DI_21.set_angle(0)
# create style style_screen_di_21_main_main_default
style_screen_di_21_main_main_default = lv.style_t()
style_screen_di_21_main_main_default.init()
style_screen_di_21_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_di_21_main_main_default.set_img_recolor_opa(0)
style_screen_di_21_main_main_default.set_img_opa(0)

# add style for screen_DI_21
screen_DI_21.add_style(style_screen_di_21_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_DI_22 = lv.img(screen)
screen_DI_22.set_pos(145,124)
screen_DI_22.set_size(36,74)
screen_DI_22.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp610765245.png','rb') as f:
        screen_DI_22_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp610765245.png')
    sys.exit()

screen_DI_22_img = lv.img_dsc_t({
  'data_size': len(screen_DI_22_img_data),
  'header': {'always_zero': 0, 'w': 36, 'h': 74, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_DI_22_img_data
})

screen_DI_22.set_src(screen_DI_22_img)
screen_DI_22.set_pivot(0,0)
screen_DI_22.set_angle(0)
# create style style_screen_di_22_main_main_default
style_screen_di_22_main_main_default = lv.style_t()
style_screen_di_22_main_main_default.init()
style_screen_di_22_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_di_22_main_main_default.set_img_recolor_opa(0)
style_screen_di_22_main_main_default.set_img_opa(0)

# add style for screen_DI_22
screen_DI_22.add_style(style_screen_di_22_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_DI_23 = lv.img(screen)
screen_DI_23.set_pos(145,124)
screen_DI_23.set_size(36,74)
screen_DI_23.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1466444098.png','rb') as f:
        screen_DI_23_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1466444098.png')
    sys.exit()

screen_DI_23_img = lv.img_dsc_t({
  'data_size': len(screen_DI_23_img_data),
  'header': {'always_zero': 0, 'w': 36, 'h': 74, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_DI_23_img_data
})

screen_DI_23.set_src(screen_DI_23_img)
screen_DI_23.set_pivot(0,0)
screen_DI_23.set_angle(0)
# create style style_screen_di_23_main_main_default
style_screen_di_23_main_main_default = lv.style_t()
style_screen_di_23_main_main_default.init()
style_screen_di_23_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_di_23_main_main_default.set_img_recolor_opa(0)
style_screen_di_23_main_main_default.set_img_opa(0)

# add style for screen_DI_23
screen_DI_23.add_style(style_screen_di_23_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_DI_24 = lv.img(screen)
screen_DI_24.set_pos(145,124)
screen_DI_24.set_size(36,74)
screen_DI_24.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp751313855.png','rb') as f:
        screen_DI_24_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp751313855.png')
    sys.exit()

screen_DI_24_img = lv.img_dsc_t({
  'data_size': len(screen_DI_24_img_data),
  'header': {'always_zero': 0, 'w': 36, 'h': 74, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_DI_24_img_data
})

screen_DI_24.set_src(screen_DI_24_img)
screen_DI_24.set_pivot(0,0)
screen_DI_24.set_angle(0)
# create style style_screen_di_24_main_main_default
style_screen_di_24_main_main_default = lv.style_t()
style_screen_di_24_main_main_default.init()
style_screen_di_24_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_di_24_main_main_default.set_img_recolor_opa(0)
style_screen_di_24_main_main_default.set_img_opa(0)

# add style for screen_DI_24
screen_DI_24.add_style(style_screen_di_24_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_D_25 = lv.img(screen)
screen_D_25.set_pos(145,124)
screen_D_25.set_size(36,74)
screen_D_25.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1325895488.png','rb') as f:
        screen_D_25_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1325895488.png')
    sys.exit()

screen_D_25_img = lv.img_dsc_t({
  'data_size': len(screen_D_25_img_data),
  'header': {'always_zero': 0, 'w': 36, 'h': 74, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_D_25_img_data
})

screen_D_25.set_src(screen_D_25_img)
screen_D_25.set_pivot(0,0)
screen_D_25.set_angle(0)
# create style style_screen_d_25_main_main_default
style_screen_d_25_main_main_default = lv.style_t()
style_screen_d_25_main_main_default.init()
style_screen_d_25_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_d_25_main_main_default.set_img_recolor_opa(0)
style_screen_d_25_main_main_default.set_img_opa(0)

# add style for screen_D_25
screen_D_25.add_style(style_screen_d_25_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_DI_26 = lv.img(screen)
screen_DI_26.set_pos(145,124)
screen_DI_26.set_size(36,74)
screen_DI_26.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp891862465.png','rb') as f:
        screen_DI_26_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp891862465.png')
    sys.exit()

screen_DI_26_img = lv.img_dsc_t({
  'data_size': len(screen_DI_26_img_data),
  'header': {'always_zero': 0, 'w': 36, 'h': 74, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_DI_26_img_data
})

screen_DI_26.set_src(screen_DI_26_img)
screen_DI_26.set_pivot(0,0)
screen_DI_26.set_angle(0)
# create style style_screen_di_26_main_main_default
style_screen_di_26_main_main_default = lv.style_t()
style_screen_di_26_main_main_default.init()
style_screen_di_26_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_di_26_main_main_default.set_img_recolor_opa(0)
style_screen_di_26_main_main_default.set_img_opa(0)

# add style for screen_DI_26
screen_DI_26.add_style(style_screen_di_26_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_DI_27 = lv.img(screen)
screen_DI_27.set_pos(145,124)
screen_DI_27.set_size(36,74)
screen_DI_27.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1185346878.png','rb') as f:
        screen_DI_27_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1185346878.png')
    sys.exit()

screen_DI_27_img = lv.img_dsc_t({
  'data_size': len(screen_DI_27_img_data),
  'header': {'always_zero': 0, 'w': 36, 'h': 74, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_DI_27_img_data
})

screen_DI_27.set_src(screen_DI_27_img)
screen_DI_27.set_pivot(0,0)
screen_DI_27.set_angle(0)
# create style style_screen_di_27_main_main_default
style_screen_di_27_main_main_default = lv.style_t()
style_screen_di_27_main_main_default.init()
style_screen_di_27_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_di_27_main_main_default.set_img_recolor_opa(0)
style_screen_di_27_main_main_default.set_img_opa(0)

# add style for screen_DI_27
screen_DI_27.add_style(style_screen_di_27_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_DI_28 = lv.img(screen)
screen_DI_28.set_pos(57,124)
screen_DI_28.set_size(35,73)
screen_DI_28.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp523573249.png','rb') as f:
        screen_DI_28_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp523573249.png')
    sys.exit()

screen_DI_28_img = lv.img_dsc_t({
  'data_size': len(screen_DI_28_img_data),
  'header': {'always_zero': 0, 'w': 35, 'h': 73, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_DI_28_img_data
})

screen_DI_28.set_src(screen_DI_28_img)
screen_DI_28.set_pivot(0,0)
screen_DI_28.set_angle(0)
# create style style_screen_di_28_main_main_default
style_screen_di_28_main_main_default = lv.style_t()
style_screen_di_28_main_main_default.init()
style_screen_di_28_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_di_28_main_main_default.set_img_recolor_opa(0)
style_screen_di_28_main_main_default.set_img_opa(0)

# add style for screen_DI_28
screen_DI_28.add_style(style_screen_di_28_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_DI_29 = lv.img(screen)
screen_DI_29.set_pos(57,124)
screen_DI_29.set_size(35,73)
screen_DI_29.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1553636094.png','rb') as f:
        screen_DI_29_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1553636094.png')
    sys.exit()

screen_DI_29_img = lv.img_dsc_t({
  'data_size': len(screen_DI_29_img_data),
  'header': {'always_zero': 0, 'w': 35, 'h': 73, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_DI_29_img_data
})

screen_DI_29.set_src(screen_DI_29_img)
screen_DI_29.set_pivot(0,0)
screen_DI_29.set_angle(0)
# create style style_screen_di_29_main_main_default
style_screen_di_29_main_main_default = lv.style_t()
style_screen_di_29_main_main_default.init()
style_screen_di_29_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_di_29_main_main_default.set_img_recolor_opa(0)
style_screen_di_29_main_main_default.set_img_opa(0)

# add style for screen_DI_29
screen_DI_29.add_style(style_screen_di_29_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_DI_30 = lv.img(screen)
screen_DI_30.set_pos(57,124)
screen_DI_30.set_size(35,73)
screen_DI_30.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp1686913777.png','rb') as f:
        screen_DI_30_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp1686913777.png')
    sys.exit()

screen_DI_30_img = lv.img_dsc_t({
  'data_size': len(screen_DI_30_img_data),
  'header': {'always_zero': 0, 'w': 35, 'h': 73, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_DI_30_img_data
})

screen_DI_30.set_src(screen_DI_30_img)
screen_DI_30.set_pivot(0,0)
screen_DI_30.set_angle(0)
# create style style_screen_di_30_main_main_default
style_screen_di_30_main_main_default = lv.style_t()
style_screen_di_30_main_main_default.init()
style_screen_di_30_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_di_30_main_main_default.set_img_recolor_opa(0)
style_screen_di_30_main_main_default.set_img_opa(0)

# add style for screen_DI_30
screen_DI_30.add_style(style_screen_di_30_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_DI_31 = lv.img(screen)
screen_DI_31.set_pos(57,124)
screen_DI_31.set_size(35,73)
screen_DI_31.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-487898948.png','rb') as f:
        screen_DI_31_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-487898948.png')
    sys.exit()

screen_DI_31_img = lv.img_dsc_t({
  'data_size': len(screen_DI_31_img_data),
  'header': {'always_zero': 0, 'w': 35, 'h': 73, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_DI_31_img_data
})

screen_DI_31.set_src(screen_DI_31_img)
screen_DI_31.set_pivot(0,0)
screen_DI_31.set_angle(0)
# create style style_screen_di_31_main_main_default
style_screen_di_31_main_main_default = lv.style_t()
style_screen_di_31_main_main_default.init()
style_screen_di_31_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_di_31_main_main_default.set_img_recolor_opa(0)
style_screen_di_31_main_main_default.set_img_opa(0)

# add style for screen_DI_31
screen_DI_31.add_style(style_screen_di_31_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_DI_32 = lv.img(screen)
screen_DI_32.set_pos(57,124)
screen_DI_32.set_size(35,73)
screen_DI_32.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp1729859005.png','rb') as f:
        screen_DI_32_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp1729859005.png')
    sys.exit()

screen_DI_32_img = lv.img_dsc_t({
  'data_size': len(screen_DI_32_img_data),
  'header': {'always_zero': 0, 'w': 35, 'h': 73, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_DI_32_img_data
})

screen_DI_32.set_src(screen_DI_32_img)
screen_DI_32.set_pivot(0,0)
screen_DI_32.set_angle(0)
# create style style_screen_di_32_main_main_default
style_screen_di_32_main_main_default = lv.style_t()
style_screen_di_32_main_main_default.init()
style_screen_di_32_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_di_32_main_main_default.set_img_recolor_opa(0)
style_screen_di_32_main_main_default.set_img_opa(0)

# add style for screen_DI_32
screen_DI_32.add_style(style_screen_di_32_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_DI_33 = lv.img(screen)
screen_DI_33.set_pos(57,124)
screen_DI_33.set_size(35,73)
screen_DI_33.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-347350338.png','rb') as f:
        screen_DI_33_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-347350338.png')
    sys.exit()

screen_DI_33_img = lv.img_dsc_t({
  'data_size': len(screen_DI_33_img_data),
  'header': {'always_zero': 0, 'w': 35, 'h': 73, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_DI_33_img_data
})

screen_DI_33.set_src(screen_DI_33_img)
screen_DI_33.set_pivot(0,0)
screen_DI_33.set_angle(0)
# create style style_screen_di_33_main_main_default
style_screen_di_33_main_main_default = lv.style_t()
style_screen_di_33_main_main_default.init()
style_screen_di_33_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_di_33_main_main_default.set_img_recolor_opa(0)
style_screen_di_33_main_main_default.set_img_opa(0)

# add style for screen_DI_33
screen_DI_33.add_style(style_screen_di_33_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_DI_34 = lv.img(screen)
screen_DI_34.set_pos(57,124)
screen_DI_34.set_size(35,73)
screen_DI_34.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp1870407615.png','rb') as f:
        screen_DI_34_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp1870407615.png')
    sys.exit()

screen_DI_34_img = lv.img_dsc_t({
  'data_size': len(screen_DI_34_img_data),
  'header': {'always_zero': 0, 'w': 35, 'h': 73, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_DI_34_img_data
})

screen_DI_34.set_src(screen_DI_34_img)
screen_DI_34.set_pivot(0,0)
screen_DI_34.set_angle(0)
# create style style_screen_di_34_main_main_default
style_screen_di_34_main_main_default = lv.style_t()
style_screen_di_34_main_main_default.init()
style_screen_di_34_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_di_34_main_main_default.set_img_recolor_opa(0)
style_screen_di_34_main_main_default.set_img_opa(0)

# add style for screen_DI_34
screen_DI_34.add_style(style_screen_di_34_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_DI_35 = lv.img(screen)
screen_DI_35.set_pos(57,124)
screen_DI_35.set_size(35,73)
screen_DI_35.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-206801728.png','rb') as f:
        screen_DI_35_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-206801728.png')
    sys.exit()

screen_DI_35_img = lv.img_dsc_t({
  'data_size': len(screen_DI_35_img_data),
  'header': {'always_zero': 0, 'w': 35, 'h': 73, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_DI_35_img_data
})

screen_DI_35.set_src(screen_DI_35_img)
screen_DI_35.set_pivot(0,0)
screen_DI_35.set_angle(0)
# create style style_screen_di_35_main_main_default
style_screen_di_35_main_main_default = lv.style_t()
style_screen_di_35_main_main_default.init()
style_screen_di_35_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_di_35_main_main_default.set_img_recolor_opa(0)
style_screen_di_35_main_main_default.set_img_opa(0)

# add style for screen_DI_35
screen_DI_35.add_style(style_screen_di_35_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_DI_37 = lv.img(screen)
screen_DI_37.set_pos(57,124)
screen_DI_37.set_size(35,73)
screen_DI_37.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp2010956225.png','rb') as f:
        screen_DI_37_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp2010956225.png')
    sys.exit()

screen_DI_37_img = lv.img_dsc_t({
  'data_size': len(screen_DI_37_img_data),
  'header': {'always_zero': 0, 'w': 35, 'h': 73, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_DI_37_img_data
})

screen_DI_37.set_src(screen_DI_37_img)
screen_DI_37.set_pivot(0,0)
screen_DI_37.set_angle(0)
# create style style_screen_di_37_main_main_default
style_screen_di_37_main_main_default = lv.style_t()
style_screen_di_37_main_main_default.init()
style_screen_di_37_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_di_37_main_main_default.set_img_recolor_opa(0)
style_screen_di_37_main_main_default.set_img_opa(0)

# add style for screen_DI_37
screen_DI_37.add_style(style_screen_di_37_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_DI_38 = lv.img(screen)
screen_DI_38.set_pos(54,124)
screen_DI_38.set_size(35,73)
screen_DI_38.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-66253118.png','rb') as f:
        screen_DI_38_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-66253118.png')
    sys.exit()

screen_DI_38_img = lv.img_dsc_t({
  'data_size': len(screen_DI_38_img_data),
  'header': {'always_zero': 0, 'w': 35, 'h': 73, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_DI_38_img_data
})

screen_DI_38.set_src(screen_DI_38_img)
screen_DI_38.set_pivot(0,0)
screen_DI_38.set_angle(0)
# create style style_screen_di_38_main_main_default
style_screen_di_38_main_main_default = lv.style_t()
style_screen_di_38_main_main_default.init()
style_screen_di_38_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_di_38_main_main_default.set_img_recolor_opa(0)
style_screen_di_38_main_main_default.set_img_opa(0)

# add style for screen_DI_38
screen_DI_38.add_style(style_screen_di_38_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_DI_39 = lv.img(screen)
screen_DI_39.set_pos(100,124)
screen_DI_39.set_size(36,74)
screen_DI_39.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1634624635.png','rb') as f:
        screen_DI_39_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1634624635.png')
    sys.exit()

screen_DI_39_img = lv.img_dsc_t({
  'data_size': len(screen_DI_39_img_data),
  'header': {'always_zero': 0, 'w': 36, 'h': 74, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_DI_39_img_data
})

screen_DI_39.set_src(screen_DI_39_img)
screen_DI_39.set_pivot(0,0)
screen_DI_39.set_angle(0)
# create style style_screen_di_39_main_main_default
style_screen_di_39_main_main_default = lv.style_t()
style_screen_di_39_main_main_default.init()
style_screen_di_39_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_di_39_main_main_default.set_img_recolor_opa(0)
style_screen_di_39_main_main_default.set_img_opa(0)

# add style for screen_DI_39
screen_DI_39.add_style(style_screen_di_39_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_DI_40 = lv.img(screen)
screen_DI_40.set_pos(100,124)
screen_DI_40.set_size(36,74)
screen_DI_40.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp583133318.png','rb') as f:
        screen_DI_40_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp583133318.png')
    sys.exit()

screen_DI_40_img = lv.img_dsc_t({
  'data_size': len(screen_DI_40_img_data),
  'header': {'always_zero': 0, 'w': 36, 'h': 74, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_DI_40_img_data
})

screen_DI_40.set_src(screen_DI_40_img)
screen_DI_40.set_pivot(0,0)
screen_DI_40.set_angle(0)
# create style style_screen_di_40_main_main_default
style_screen_di_40_main_main_default = lv.style_t()
style_screen_di_40_main_main_default.init()
style_screen_di_40_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_di_40_main_main_default.set_img_recolor_opa(0)
style_screen_di_40_main_main_default.set_img_opa(0)

# add style for screen_DI_40
screen_DI_40.add_style(style_screen_di_40_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_Whit_Img = lv.img(screen)
screen_Whit_Img.set_pos(48,99)
screen_Whit_Img.set_size(9,9)
screen_Whit_Img.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp2092450693.png','rb') as f:
        screen_Whit_Img_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp2092450693.png')
    sys.exit()

screen_Whit_Img_img = lv.img_dsc_t({
  'data_size': len(screen_Whit_Img_img_data),
  'header': {'always_zero': 0, 'w': 9, 'h': 9, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_Whit_Img_img_data
})

screen_Whit_Img.set_src(screen_Whit_Img_img)
screen_Whit_Img.set_pivot(0,0)
screen_Whit_Img.set_angle(0)
# create style style_screen_whit_img_main_main_default
style_screen_whit_img_main_main_default = lv.style_t()
style_screen_whit_img_main_main_default.init()
style_screen_whit_img_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_whit_img_main_main_default.set_img_recolor_opa(0)
style_screen_whit_img_main_main_default.set_img_opa(255)

# add style for screen_Whit_Img
screen_Whit_Img.add_style(style_screen_whit_img_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_img_An_1 = lv.img(screen)
screen_img_An_1.set_pos(0,0)
screen_img_An_1.set_size(240,320)
screen_img_An_1.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-369897119.png','rb') as f:
        screen_img_An_1_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-369897119.png')
    sys.exit()

screen_img_An_1_img = lv.img_dsc_t({
  'data_size': len(screen_img_An_1_img_data),
  'header': {'always_zero': 0, 'w': 240, 'h': 320, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_img_An_1_img_data
})

screen_img_An_1.set_src(screen_img_An_1_img)
screen_img_An_1.set_pivot(0,0)
screen_img_An_1.set_angle(0)
# create style style_screen_img_an_1_main_main_default
style_screen_img_an_1_main_main_default = lv.style_t()
style_screen_img_an_1_main_main_default.init()
style_screen_img_an_1_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_img_an_1_main_main_default.set_img_recolor_opa(0)
style_screen_img_an_1_main_main_default.set_img_opa(0)

# add style for screen_img_An_1
screen_img_An_1.add_style(style_screen_img_an_1_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_D_A_Icon = lv.img(screen)
screen_D_A_Icon.set_pos(105,252)
screen_D_A_Icon.set_size(30,30)
screen_D_A_Icon.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp1331036151.png','rb') as f:
        screen_D_A_Icon_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp1331036151.png')
    sys.exit()

screen_D_A_Icon_img = lv.img_dsc_t({
  'data_size': len(screen_D_A_Icon_img_data),
  'header': {'always_zero': 0, 'w': 30, 'h': 30, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_D_A_Icon_img_data
})

screen_D_A_Icon.set_src(screen_D_A_Icon_img)
screen_D_A_Icon.set_pivot(0,0)
screen_D_A_Icon.set_angle(0)
# create style style_screen_d_a_icon_main_main_default
style_screen_d_a_icon_main_main_default = lv.style_t()
style_screen_d_a_icon_main_main_default.init()
style_screen_d_a_icon_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_d_a_icon_main_main_default.set_img_recolor_opa(0)
style_screen_d_a_icon_main_main_default.set_img_opa(0)

# add style for screen_D_A_Icon
screen_D_A_Icon.add_style(style_screen_d_a_icon_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_D_B_Icon = lv.img(screen)
screen_D_B_Icon.set_pos(105,252)
screen_D_B_Icon.set_size(30,30)
screen_D_B_Icon.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-2002317128.png','rb') as f:
        screen_D_B_Icon_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-2002317128.png')
    sys.exit()

screen_D_B_Icon_img = lv.img_dsc_t({
  'data_size': len(screen_D_B_Icon_img_data),
  'header': {'always_zero': 0, 'w': 30, 'h': 30, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_D_B_Icon_img_data
})

screen_D_B_Icon.set_src(screen_D_B_Icon_img)
screen_D_B_Icon.set_pivot(0,0)
screen_D_B_Icon.set_angle(0)
# create style style_screen_d_b_icon_main_main_default
style_screen_d_b_icon_main_main_default = lv.style_t()
style_screen_d_b_icon_main_main_default.init()
style_screen_d_b_icon_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_d_b_icon_main_main_default.set_img_recolor_opa(0)
style_screen_d_b_icon_main_main_default.set_img_opa(0)

# add style for screen_D_B_Icon
screen_D_B_Icon.add_style(style_screen_d_b_icon_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_D_Up_A = lv.img(screen)
screen_D_Up_A.set_pos(31,135)
screen_D_Up_A.set_size(13,9)
screen_D_Up_A.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp155926873.png','rb') as f:
        screen_D_Up_A_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp155926873.png')
    sys.exit()

screen_D_Up_A_img = lv.img_dsc_t({
  'data_size': len(screen_D_Up_A_img_data),
  'header': {'always_zero': 0, 'w': 13, 'h': 9, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_D_Up_A_img_data
})

screen_D_Up_A.set_src(screen_D_Up_A_img)
screen_D_Up_A.set_pivot(0,0)
screen_D_Up_A.set_angle(0)
# create style style_screen_d_up_a_main_main_default
style_screen_d_up_a_main_main_default = lv.style_t()
style_screen_d_up_a_main_main_default.init()
style_screen_d_up_a_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_d_up_a_main_main_default.set_img_recolor_opa(0)
style_screen_d_up_a_main_main_default.set_img_opa(255)

# add style for screen_D_Up_A
screen_D_Up_A.add_style(style_screen_d_up_a_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_D_Down_A = lv.img(screen)
screen_D_Down_A.set_pos(31,178)
screen_D_Down_A.set_size(13,9)
screen_D_Down_A.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-329609184.png','rb') as f:
        screen_D_Down_A_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-329609184.png')
    sys.exit()

screen_D_Down_A_img = lv.img_dsc_t({
  'data_size': len(screen_D_Down_A_img_data),
  'header': {'always_zero': 0, 'w': 13, 'h': 9, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_D_Down_A_img_data
})

screen_D_Down_A.set_src(screen_D_Down_A_img)
screen_D_Down_A.set_pivot(0,0)
screen_D_Down_A.set_angle(0)
# create style style_screen_d_down_a_main_main_default
style_screen_d_down_a_main_main_default = lv.style_t()
style_screen_d_down_a_main_main_default.init()
style_screen_d_down_a_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_d_down_a_main_main_default.set_img_recolor_opa(0)
style_screen_d_down_a_main_main_default.set_img_opa(255)

# add style for screen_D_Down_A
screen_D_Down_A.add_style(style_screen_d_down_a_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_Whi_gear = lv.img(screen)
screen_Whi_gear.set_pos(17,148)
screen_Whi_gear.set_size(10,24)
screen_Whi_gear.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-626985607.png','rb') as f:
        screen_Whi_gear_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-626985607.png')
    sys.exit()

screen_Whi_gear_img = lv.img_dsc_t({
  'data_size': len(screen_Whi_gear_img_data),
  'header': {'always_zero': 0, 'w': 10, 'h': 24, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_Whi_gear_img_data
})

screen_Whi_gear.set_src(screen_Whi_gear_img)
screen_Whi_gear.set_pivot(0,0)
screen_Whi_gear.set_angle(0)
# create style style_screen_whi_gear_main_main_default
style_screen_whi_gear_main_main_default = lv.style_t()
style_screen_whi_gear_main_main_default.init()
style_screen_whi_gear_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_whi_gear_main_main_default.set_img_recolor_opa(0)
style_screen_whi_gear_main_main_default.set_img_opa(255)

# add style for screen_Whi_gear
screen_Whi_gear.add_style(style_screen_whi_gear_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_contscr_1 = lv.obj(screen)
screen_contscr_1.set_pos(30,167)
screen_contscr_1.set_size(195,78)
screen_L1_lbl = lv.label(screen_contscr_1)
screen_L1_lbl.set_pos(0,21)
screen_L1_lbl.set_size(79,17)
screen_L1_lbl.set_text("Av Speed")
screen_L1_lbl.set_long_mode(lv.label.LONG.CLIP)
screen_L1_lbl.set_style_text_align(lv.TEXT_ALIGN.RIGHT, 0)
# create style style_screen_l1_lbl_main_main_default
style_screen_l1_lbl_main_main_default = lv.style_t()
style_screen_l1_lbl_main_main_default.init()
style_screen_l1_lbl_main_main_default.set_radius(0)
style_screen_l1_lbl_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_screen_l1_lbl_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_l1_lbl_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_screen_l1_lbl_main_main_default.set_bg_opa(0)
style_screen_l1_lbl_main_main_default.set_text_color(lv.color_make(0xff,0x78,0x00))
try:
    style_screen_l1_lbl_main_main_default.set_text_font(lv.font_FjallaOne_Regular_17)
except AttributeError:
    try:
        style_screen_l1_lbl_main_main_default.set_text_font(lv.font_montserrat_17)
    except AttributeError:
        style_screen_l1_lbl_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_l1_lbl_main_main_default.set_text_letter_space(0)
style_screen_l1_lbl_main_main_default.set_pad_left(0)
style_screen_l1_lbl_main_main_default.set_pad_right(0)
style_screen_l1_lbl_main_main_default.set_pad_top(0)
style_screen_l1_lbl_main_main_default.set_pad_bottom(0)

# add style for screen_L1_lbl
screen_L1_lbl.add_style(style_screen_l1_lbl_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_L1_val = lv.label(screen_contscr_1)
screen_L1_val.set_pos(81,18)
screen_L1_val.set_size(48,18)
screen_L1_val.set_text("123.9")
screen_L1_val.set_long_mode(lv.label.LONG.CLIP)
screen_L1_val.set_style_text_align(lv.TEXT_ALIGN.RIGHT, 0)
# create style style_screen_l1_val_main_main_default
style_screen_l1_val_main_main_default = lv.style_t()
style_screen_l1_val_main_main_default.init()
style_screen_l1_val_main_main_default.set_radius(0)
style_screen_l1_val_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_screen_l1_val_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_l1_val_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_screen_l1_val_main_main_default.set_bg_opa(0)
style_screen_l1_val_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_screen_l1_val_main_main_default.set_text_font(lv.font_FjallaOne_Regular_22)
except AttributeError:
    try:
        style_screen_l1_val_main_main_default.set_text_font(lv.font_montserrat_22)
    except AttributeError:
        style_screen_l1_val_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_l1_val_main_main_default.set_text_letter_space(0)
style_screen_l1_val_main_main_default.set_pad_left(0)
style_screen_l1_val_main_main_default.set_pad_right(0)
style_screen_l1_val_main_main_default.set_pad_top(0)
style_screen_l1_val_main_main_default.set_pad_bottom(0)

# add style for screen_L1_val
screen_L1_val.add_style(style_screen_l1_val_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_L1_unit = lv.label(screen_contscr_1)
screen_L1_unit.set_pos(131,21)
screen_L1_unit.set_size(56,19)
screen_L1_unit.set_text("L/100km")
screen_L1_unit.set_long_mode(lv.label.LONG.CLIP)
screen_L1_unit.set_style_text_align(lv.TEXT_ALIGN.LEFT, 0)
# create style style_screen_l1_unit_main_main_default
style_screen_l1_unit_main_main_default = lv.style_t()
style_screen_l1_unit_main_main_default.init()
style_screen_l1_unit_main_main_default.set_radius(0)
style_screen_l1_unit_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_screen_l1_unit_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_l1_unit_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_screen_l1_unit_main_main_default.set_bg_opa(0)
style_screen_l1_unit_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_screen_l1_unit_main_main_default.set_text_font(lv.font_FjallaOne_Regular_17)
except AttributeError:
    try:
        style_screen_l1_unit_main_main_default.set_text_font(lv.font_montserrat_17)
    except AttributeError:
        style_screen_l1_unit_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_l1_unit_main_main_default.set_text_letter_space(0)
style_screen_l1_unit_main_main_default.set_pad_left(0)
style_screen_l1_unit_main_main_default.set_pad_right(0)
style_screen_l1_unit_main_main_default.set_pad_top(0)
style_screen_l1_unit_main_main_default.set_pad_bottom(0)

# add style for screen_L1_unit
screen_L1_unit.add_style(style_screen_l1_unit_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_L2_lbl = lv.label(screen_contscr_1)
screen_L2_lbl.set_pos(0,47)
screen_L2_lbl.set_size(79,17)
screen_L2_lbl.set_text("Service Due")
screen_L2_lbl.set_long_mode(lv.label.LONG.CLIP)
screen_L2_lbl.set_style_text_align(lv.TEXT_ALIGN.RIGHT, 0)
# create style style_screen_l2_lbl_main_main_default
style_screen_l2_lbl_main_main_default = lv.style_t()
style_screen_l2_lbl_main_main_default.init()
style_screen_l2_lbl_main_main_default.set_radius(0)
style_screen_l2_lbl_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_screen_l2_lbl_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_l2_lbl_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_screen_l2_lbl_main_main_default.set_bg_opa(0)
style_screen_l2_lbl_main_main_default.set_text_color(lv.color_make(0xff,0x78,0x00))
try:
    style_screen_l2_lbl_main_main_default.set_text_font(lv.font_FjallaOne_Regular_17)
except AttributeError:
    try:
        style_screen_l2_lbl_main_main_default.set_text_font(lv.font_montserrat_17)
    except AttributeError:
        style_screen_l2_lbl_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_l2_lbl_main_main_default.set_text_letter_space(0)
style_screen_l2_lbl_main_main_default.set_pad_left(0)
style_screen_l2_lbl_main_main_default.set_pad_right(0)
style_screen_l2_lbl_main_main_default.set_pad_top(0)
style_screen_l2_lbl_main_main_default.set_pad_bottom(0)

# add style for screen_L2_lbl
screen_L2_lbl.add_style(style_screen_l2_lbl_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_L2_val = lv.label(screen_contscr_1)
screen_L2_val.set_pos(81,45)
screen_L2_val.set_size(104,18)
screen_L2_val.set_text("00 h 00m")
screen_L2_val.set_long_mode(lv.label.LONG.CLIP)
screen_L2_val.set_style_text_align(lv.TEXT_ALIGN.RIGHT, 0)
# create style style_screen_l2_val_main_main_default
style_screen_l2_val_main_main_default = lv.style_t()
style_screen_l2_val_main_main_default.init()
style_screen_l2_val_main_main_default.set_radius(0)
style_screen_l2_val_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_screen_l2_val_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_l2_val_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_screen_l2_val_main_main_default.set_bg_opa(0)
style_screen_l2_val_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_screen_l2_val_main_main_default.set_text_font(lv.font_FjallaOne_Regular_22)
except AttributeError:
    try:
        style_screen_l2_val_main_main_default.set_text_font(lv.font_montserrat_22)
    except AttributeError:
        style_screen_l2_val_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_l2_val_main_main_default.set_text_letter_space(0)
style_screen_l2_val_main_main_default.set_pad_left(0)
style_screen_l2_val_main_main_default.set_pad_right(0)
style_screen_l2_val_main_main_default.set_pad_top(0)
style_screen_l2_val_main_main_default.set_pad_bottom(0)

# add style for screen_L2_val
screen_L2_val.add_style(style_screen_l2_val_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_L2_unit = lv.label(screen_contscr_1)
screen_L2_unit.set_pos(131,46)
screen_L2_unit.set_size(56,19)
screen_L2_unit.set_text("L/100km")
screen_L2_unit.set_long_mode(lv.label.LONG.CLIP)
screen_L2_unit.set_style_text_align(lv.TEXT_ALIGN.LEFT, 0)
# create style style_screen_l2_unit_main_main_default
style_screen_l2_unit_main_main_default = lv.style_t()
style_screen_l2_unit_main_main_default.init()
style_screen_l2_unit_main_main_default.set_radius(0)
style_screen_l2_unit_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_screen_l2_unit_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_l2_unit_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_screen_l2_unit_main_main_default.set_bg_opa(0)
style_screen_l2_unit_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_screen_l2_unit_main_main_default.set_text_font(lv.font_FjallaOne_Regular_17)
except AttributeError:
    try:
        style_screen_l2_unit_main_main_default.set_text_font(lv.font_montserrat_17)
    except AttributeError:
        style_screen_l2_unit_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_l2_unit_main_main_default.set_text_letter_space(0)
style_screen_l2_unit_main_main_default.set_pad_left(0)
style_screen_l2_unit_main_main_default.set_pad_right(0)
style_screen_l2_unit_main_main_default.set_pad_top(0)
style_screen_l2_unit_main_main_default.set_pad_bottom(0)

# add style for screen_L2_unit
screen_L2_unit.add_style(style_screen_l2_unit_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_up_arr = lv.img(screen_contscr_1)
screen_up_arr.set_pos(82,2)
screen_up_arr.set_size(12,7)
screen_up_arr.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp413900106.png','rb') as f:
        screen_up_arr_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp413900106.png')
    sys.exit()

screen_up_arr_img = lv.img_dsc_t({
  'data_size': len(screen_up_arr_img_data),
  'header': {'always_zero': 0, 'w': 12, 'h': 7, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_up_arr_img_data
})

screen_up_arr.set_src(screen_up_arr_img)
screen_up_arr.set_pivot(0,0)
screen_up_arr.set_angle(0)
# create style style_screen_up_arr_main_main_default
style_screen_up_arr_main_main_default = lv.style_t()
style_screen_up_arr_main_main_default.init()
style_screen_up_arr_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_up_arr_main_main_default.set_img_recolor_opa(0)
style_screen_up_arr_main_main_default.set_img_opa(255)

# add style for screen_up_arr
screen_up_arr.add_style(style_screen_up_arr_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_dw_arr = lv.img(screen_contscr_1)
screen_dw_arr.set_pos(82,70)
screen_dw_arr.set_size(12,7)
screen_dw_arr.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1021886939.png','rb') as f:
        screen_dw_arr_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1021886939.png')
    sys.exit()

screen_dw_arr_img = lv.img_dsc_t({
  'data_size': len(screen_dw_arr_img_data),
  'header': {'always_zero': 0, 'w': 12, 'h': 7, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_dw_arr_img_data
})

screen_dw_arr.set_src(screen_dw_arr_img)
screen_dw_arr.set_pivot(0,0)
screen_dw_arr.set_angle(0)
# create style style_screen_dw_arr_main_main_default
style_screen_dw_arr_main_main_default = lv.style_t()
style_screen_dw_arr_main_main_default.init()
style_screen_dw_arr_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_dw_arr_main_main_default.set_img_recolor_opa(0)
style_screen_dw_arr_main_main_default.set_img_opa(255)

# add style for screen_dw_arr
screen_dw_arr.add_style(style_screen_dw_arr_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_screen_contscr_1_main_main_default
style_screen_contscr_1_main_main_default = lv.style_t()
style_screen_contscr_1_main_main_default.init()
style_screen_contscr_1_main_main_default.set_radius(0)
style_screen_contscr_1_main_main_default.set_bg_color(lv.color_make(0x00,0x00,0x00))
style_screen_contscr_1_main_main_default.set_bg_grad_color(lv.color_make(0x08,0x08,0x08))
style_screen_contscr_1_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_screen_contscr_1_main_main_default.set_bg_opa(0)
style_screen_contscr_1_main_main_default.set_border_color(lv.color_make(0x00,0x00,0x00))
style_screen_contscr_1_main_main_default.set_border_width(0)
style_screen_contscr_1_main_main_default.set_border_opa(0)
style_screen_contscr_1_main_main_default.set_pad_left(0)
style_screen_contscr_1_main_main_default.set_pad_right(0)
style_screen_contscr_1_main_main_default.set_pad_top(0)
style_screen_contscr_1_main_main_default.set_pad_bottom(0)

# add style for screen_contscr_1
screen_contscr_1.add_style(style_screen_contscr_1_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_contSp_Main_2 = lv.obj(screen)
screen_contSp_Main_2.set_pos(56,120)
screen_contSp_Main_2.set_size(136,123)
screen_con_odo_val = lv.label(screen_contSp_Main_2)
screen_con_odo_val.set_pos(38,99)
screen_con_odo_val.set_size(69,19)
screen_con_odo_val.set_text("999")
screen_con_odo_val.set_long_mode(lv.label.LONG.WRAP)
screen_con_odo_val.set_style_text_align(lv.TEXT_ALIGN.RIGHT, 0)
# create style style_screen_con_odo_val_main_main_default
style_screen_con_odo_val_main_main_default = lv.style_t()
style_screen_con_odo_val_main_main_default.init()
style_screen_con_odo_val_main_main_default.set_radius(0)
style_screen_con_odo_val_main_main_default.set_bg_color(lv.color_make(0x00,0x00,0x00))
style_screen_con_odo_val_main_main_default.set_bg_grad_color(lv.color_make(0x00,0x00,0x00))
style_screen_con_odo_val_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_screen_con_odo_val_main_main_default.set_bg_opa(255)
style_screen_con_odo_val_main_main_default.set_text_color(lv.color_make(0xff,0x78,0x00))
try:
    style_screen_con_odo_val_main_main_default.set_text_font(lv.font_FjallaOne_Regular_22)
except AttributeError:
    try:
        style_screen_con_odo_val_main_main_default.set_text_font(lv.font_montserrat_22)
    except AttributeError:
        style_screen_con_odo_val_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_con_odo_val_main_main_default.set_text_letter_space(0)
style_screen_con_odo_val_main_main_default.set_pad_left(0)
style_screen_con_odo_val_main_main_default.set_pad_right(0)
style_screen_con_odo_val_main_main_default.set_pad_top(0)
style_screen_con_odo_val_main_main_default.set_pad_bottom(0)

# add style for screen_con_odo_val
screen_con_odo_val.add_style(style_screen_con_odo_val_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_Codo = lv.img(screen_contSp_Main_2)
screen_Codo.set_pos(2,103)
screen_Codo.set_size(27,14)
screen_Codo.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp1052416217.png','rb') as f:
        screen_Codo_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp1052416217.png')
    sys.exit()

screen_Codo_img = lv.img_dsc_t({
  'data_size': len(screen_Codo_img_data),
  'header': {'always_zero': 0, 'w': 27, 'h': 14, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_Codo_img_data
})

screen_Codo.set_src(screen_Codo_img)
screen_Codo.set_pivot(0,0)
screen_Codo.set_angle(0)
# create style style_screen_codo_main_main_default
style_screen_codo_main_main_default = lv.style_t()
style_screen_codo_main_main_default.init()
style_screen_codo_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_codo_main_main_default.set_img_recolor_opa(0)
style_screen_codo_main_main_default.set_img_opa(255)

# add style for screen_Codo
screen_Codo.add_style(style_screen_codo_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_conkm = lv.img(screen_contSp_Main_2)
screen_conkm.set_pos(110,102)
screen_conkm.set_size(20,15)
screen_conkm.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1725238764.png','rb') as f:
        screen_conkm_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1725238764.png')
    sys.exit()

screen_conkm_img = lv.img_dsc_t({
  'data_size': len(screen_conkm_img_data),
  'header': {'always_zero': 0, 'w': 20, 'h': 15, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_conkm_img_data
})

screen_conkm.set_src(screen_conkm_img)
screen_conkm.set_pivot(0,0)
screen_conkm.set_angle(0)
# create style style_screen_conkm_main_main_default
style_screen_conkm_main_main_default = lv.style_t()
style_screen_conkm_main_main_default.init()
style_screen_conkm_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_conkm_main_main_default.set_img_recolor_opa(0)
style_screen_conkm_main_main_default.set_img_opa(255)

# add style for screen_conkm
screen_conkm.add_style(style_screen_conkm_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_SC_1 = lv.img(screen_contSp_Main_2)
screen_SC_1.set_pos(4,2)
screen_SC_1.set_size(39,69)
screen_SC_1.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1812948223.png','rb') as f:
        screen_SC_1_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1812948223.png')
    sys.exit()

screen_SC_1_img = lv.img_dsc_t({
  'data_size': len(screen_SC_1_img_data),
  'header': {'always_zero': 0, 'w': 39, 'h': 69, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_SC_1_img_data
})

screen_SC_1.set_src(screen_SC_1_img)
screen_SC_1.set_pivot(0,0)
screen_SC_1.set_angle(0)
# create style style_screen_sc_1_main_main_default
style_screen_sc_1_main_main_default = lv.style_t()
style_screen_sc_1_main_main_default.init()
style_screen_sc_1_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_sc_1_main_main_default.set_img_recolor_opa(0)
style_screen_sc_1_main_main_default.set_img_opa(255)

# add style for screen_SC_1
screen_SC_1.add_style(style_screen_sc_1_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_SC_2 = lv.img(screen_contSp_Main_2)
screen_SC_2.set_pos(45,2)
screen_SC_2.set_size(39,69)
screen_SC_2.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1812948223.png','rb') as f:
        screen_SC_2_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1812948223.png')
    sys.exit()

screen_SC_2_img = lv.img_dsc_t({
  'data_size': len(screen_SC_2_img_data),
  'header': {'always_zero': 0, 'w': 39, 'h': 69, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_SC_2_img_data
})

screen_SC_2.set_src(screen_SC_2_img)
screen_SC_2.set_pivot(0,0)
screen_SC_2.set_angle(0)
# create style style_screen_sc_2_main_main_default
style_screen_sc_2_main_main_default = lv.style_t()
style_screen_sc_2_main_main_default.init()
style_screen_sc_2_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_sc_2_main_main_default.set_img_recolor_opa(0)
style_screen_sc_2_main_main_default.set_img_opa(255)

# add style for screen_SC_2
screen_SC_2.add_style(style_screen_sc_2_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_SC_3 = lv.img(screen_contSp_Main_2)
screen_SC_3.set_pos(87,2)
screen_SC_3.set_size(39,69)
screen_SC_3.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1812948223.png','rb') as f:
        screen_SC_3_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1812948223.png')
    sys.exit()

screen_SC_3_img = lv.img_dsc_t({
  'data_size': len(screen_SC_3_img_data),
  'header': {'always_zero': 0, 'w': 39, 'h': 69, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_SC_3_img_data
})

screen_SC_3.set_src(screen_SC_3_img)
screen_SC_3.set_pivot(0,0)
screen_SC_3.set_angle(0)
# create style style_screen_sc_3_main_main_default
style_screen_sc_3_main_main_default = lv.style_t()
style_screen_sc_3_main_main_default.init()
style_screen_sc_3_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_sc_3_main_main_default.set_img_recolor_opa(0)
style_screen_sc_3_main_main_default.set_img_opa(255)

# add style for screen_SC_3
screen_SC_3.add_style(style_screen_sc_3_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_screen_contsp_main_2_main_main_default
style_screen_contsp_main_2_main_main_default = lv.style_t()
style_screen_contsp_main_2_main_main_default.init()
style_screen_contsp_main_2_main_main_default.set_radius(0)
style_screen_contsp_main_2_main_main_default.set_bg_color(lv.color_make(0x00,0x00,0x00))
style_screen_contsp_main_2_main_main_default.set_bg_grad_color(lv.color_make(0x00,0x00,0x00))
style_screen_contsp_main_2_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_screen_contsp_main_2_main_main_default.set_bg_opa(255)
style_screen_contsp_main_2_main_main_default.set_border_color(lv.color_make(0xff,0xff,0xff))
style_screen_contsp_main_2_main_main_default.set_border_width(0)
style_screen_contsp_main_2_main_main_default.set_border_opa(255)
style_screen_contsp_main_2_main_main_default.set_pad_left(0)
style_screen_contsp_main_2_main_main_default.set_pad_right(0)
style_screen_contsp_main_2_main_main_default.set_pad_top(0)
style_screen_contsp_main_2_main_main_default.set_pad_bottom(0)

# add style for screen_contSp_Main_2
screen_contSp_Main_2.add_style(style_screen_contsp_main_2_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_trip_spedo_cont = lv.obj(screen)
screen_trip_spedo_cont.set_pos(57,97)
screen_trip_spedo_cont.set_size(134,67)
screen_SPD_Int_9 = lv.img(screen_trip_spedo_cont)
screen_SPD_Int_9.set_pos(76,-1)
screen_SPD_Int_9.set_size(24,47)
screen_SPD_Int_9.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp1728514539.png','rb') as f:
        screen_SPD_Int_9_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp1728514539.png')
    sys.exit()

screen_SPD_Int_9_img = lv.img_dsc_t({
  'data_size': len(screen_SPD_Int_9_img_data),
  'header': {'always_zero': 0, 'w': 24, 'h': 47, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_SPD_Int_9_img_data
})

screen_SPD_Int_9.set_src(screen_SPD_Int_9_img)
screen_SPD_Int_9.set_pivot(0,0)
screen_SPD_Int_9.set_angle(0)
# create style style_screen_spd_int_9_main_main_default
style_screen_spd_int_9_main_main_default = lv.style_t()
style_screen_spd_int_9_main_main_default.init()
style_screen_spd_int_9_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_spd_int_9_main_main_default.set_img_recolor_opa(0)
style_screen_spd_int_9_main_main_default.set_img_opa(0)

# add style for screen_SPD_Int_9
screen_SPD_Int_9.add_style(style_screen_spd_int_9_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_SPD_Int_8 = lv.img(screen_trip_spedo_cont)
screen_SPD_Int_8.set_pos(76,-1)
screen_SPD_Int_8.set_size(24,47)
screen_SPD_Int_8.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-489243414.png','rb') as f:
        screen_SPD_Int_8_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-489243414.png')
    sys.exit()

screen_SPD_Int_8_img = lv.img_dsc_t({
  'data_size': len(screen_SPD_Int_8_img_data),
  'header': {'always_zero': 0, 'w': 24, 'h': 47, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_SPD_Int_8_img_data
})

screen_SPD_Int_8.set_src(screen_SPD_Int_8_img)
screen_SPD_Int_8.set_pivot(0,0)
screen_SPD_Int_8.set_angle(0)
# create style style_screen_spd_int_8_main_main_default
style_screen_spd_int_8_main_main_default = lv.style_t()
style_screen_spd_int_8_main_main_default.init()
style_screen_spd_int_8_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_spd_int_8_main_main_default.set_img_recolor_opa(0)
style_screen_spd_int_8_main_main_default.set_img_opa(0)

# add style for screen_SPD_Int_8
screen_SPD_Int_8.add_style(style_screen_spd_int_8_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_SPD_Int_7 = lv.img(screen_trip_spedo_cont)
screen_SPD_Int_7.set_pos(76,-1)
screen_SPD_Int_7.set_size(24,47)
screen_SPD_Int_7.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp1587965929.png','rb') as f:
        screen_SPD_Int_7_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp1587965929.png')
    sys.exit()

screen_SPD_Int_7_img = lv.img_dsc_t({
  'data_size': len(screen_SPD_Int_7_img_data),
  'header': {'always_zero': 0, 'w': 24, 'h': 47, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_SPD_Int_7_img_data
})

screen_SPD_Int_7.set_src(screen_SPD_Int_7_img)
screen_SPD_Int_7.set_pivot(0,0)
screen_SPD_Int_7.set_angle(0)
# create style style_screen_spd_int_7_main_main_default
style_screen_spd_int_7_main_main_default = lv.style_t()
style_screen_spd_int_7_main_main_default.init()
style_screen_spd_int_7_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_spd_int_7_main_main_default.set_img_recolor_opa(0)
style_screen_spd_int_7_main_main_default.set_img_opa(0)

# add style for screen_SPD_Int_7
screen_SPD_Int_7.add_style(style_screen_spd_int_7_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_SPD_Int_6 = lv.img(screen_trip_spedo_cont)
screen_SPD_Int_6.set_pos(76,-1)
screen_SPD_Int_6.set_size(24,47)
screen_SPD_Int_6.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-629792024.png','rb') as f:
        screen_SPD_Int_6_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-629792024.png')
    sys.exit()

screen_SPD_Int_6_img = lv.img_dsc_t({
  'data_size': len(screen_SPD_Int_6_img_data),
  'header': {'always_zero': 0, 'w': 24, 'h': 47, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_SPD_Int_6_img_data
})

screen_SPD_Int_6.set_src(screen_SPD_Int_6_img)
screen_SPD_Int_6.set_pivot(0,0)
screen_SPD_Int_6.set_angle(0)
# create style style_screen_spd_int_6_main_main_default
style_screen_spd_int_6_main_main_default = lv.style_t()
style_screen_spd_int_6_main_main_default.init()
style_screen_spd_int_6_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_spd_int_6_main_main_default.set_img_recolor_opa(0)
style_screen_spd_int_6_main_main_default.set_img_opa(0)

# add style for screen_SPD_Int_6
screen_SPD_Int_6.add_style(style_screen_spd_int_6_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_SPD_Int_5 = lv.img(screen_trip_spedo_cont)
screen_SPD_Int_5.set_pos(76,-1)
screen_SPD_Int_5.set_size(24,47)
screen_SPD_Int_5.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp1447417319.png','rb') as f:
        screen_SPD_Int_5_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp1447417319.png')
    sys.exit()

screen_SPD_Int_5_img = lv.img_dsc_t({
  'data_size': len(screen_SPD_Int_5_img_data),
  'header': {'always_zero': 0, 'w': 24, 'h': 47, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_SPD_Int_5_img_data
})

screen_SPD_Int_5.set_src(screen_SPD_Int_5_img)
screen_SPD_Int_5.set_pivot(0,0)
screen_SPD_Int_5.set_angle(0)
# create style style_screen_spd_int_5_main_main_default
style_screen_spd_int_5_main_main_default = lv.style_t()
style_screen_spd_int_5_main_main_default.init()
style_screen_spd_int_5_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_spd_int_5_main_main_default.set_img_recolor_opa(0)
style_screen_spd_int_5_main_main_default.set_img_opa(0)

# add style for screen_SPD_Int_5
screen_SPD_Int_5.add_style(style_screen_spd_int_5_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_SPD_Int_4 = lv.img(screen_trip_spedo_cont)
screen_SPD_Int_4.set_pos(76,-1)
screen_SPD_Int_4.set_size(24,47)
screen_SPD_Int_4.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-770340634.png','rb') as f:
        screen_SPD_Int_4_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-770340634.png')
    sys.exit()

screen_SPD_Int_4_img = lv.img_dsc_t({
  'data_size': len(screen_SPD_Int_4_img_data),
  'header': {'always_zero': 0, 'w': 24, 'h': 47, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_SPD_Int_4_img_data
})

screen_SPD_Int_4.set_src(screen_SPD_Int_4_img)
screen_SPD_Int_4.set_pivot(0,0)
screen_SPD_Int_4.set_angle(0)
# create style style_screen_spd_int_4_main_main_default
style_screen_spd_int_4_main_main_default = lv.style_t()
style_screen_spd_int_4_main_main_default.init()
style_screen_spd_int_4_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_spd_int_4_main_main_default.set_img_recolor_opa(0)
style_screen_spd_int_4_main_main_default.set_img_opa(0)

# add style for screen_SPD_Int_4
screen_SPD_Int_4.add_style(style_screen_spd_int_4_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_SPD_Int_3 = lv.img(screen_trip_spedo_cont)
screen_SPD_Int_3.set_pos(76,-1)
screen_SPD_Int_3.set_size(24,47)
screen_SPD_Int_3.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp1306868709.png','rb') as f:
        screen_SPD_Int_3_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp1306868709.png')
    sys.exit()

screen_SPD_Int_3_img = lv.img_dsc_t({
  'data_size': len(screen_SPD_Int_3_img_data),
  'header': {'always_zero': 0, 'w': 24, 'h': 47, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_SPD_Int_3_img_data
})

screen_SPD_Int_3.set_src(screen_SPD_Int_3_img)
screen_SPD_Int_3.set_pivot(0,0)
screen_SPD_Int_3.set_angle(0)
# create style style_screen_spd_int_3_main_main_default
style_screen_spd_int_3_main_main_default = lv.style_t()
style_screen_spd_int_3_main_main_default.init()
style_screen_spd_int_3_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_spd_int_3_main_main_default.set_img_recolor_opa(0)
style_screen_spd_int_3_main_main_default.set_img_opa(0)

# add style for screen_SPD_Int_3
screen_SPD_Int_3.add_style(style_screen_spd_int_3_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_SPD_Int_2 = lv.img(screen_trip_spedo_cont)
screen_SPD_Int_2.set_pos(76,-1)
screen_SPD_Int_2.set_size(24,47)
screen_SPD_Int_2.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-910889244.png','rb') as f:
        screen_SPD_Int_2_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-910889244.png')
    sys.exit()

screen_SPD_Int_2_img = lv.img_dsc_t({
  'data_size': len(screen_SPD_Int_2_img_data),
  'header': {'always_zero': 0, 'w': 24, 'h': 47, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_SPD_Int_2_img_data
})

screen_SPD_Int_2.set_src(screen_SPD_Int_2_img)
screen_SPD_Int_2.set_pivot(0,0)
screen_SPD_Int_2.set_angle(0)
# create style style_screen_spd_int_2_main_main_default
style_screen_spd_int_2_main_main_default = lv.style_t()
style_screen_spd_int_2_main_main_default.init()
style_screen_spd_int_2_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_spd_int_2_main_main_default.set_img_recolor_opa(0)
style_screen_spd_int_2_main_main_default.set_img_opa(0)

# add style for screen_SPD_Int_2
screen_SPD_Int_2.add_style(style_screen_spd_int_2_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_SPD_Int_1 = lv.img(screen_trip_spedo_cont)
screen_SPD_Int_1.set_pos(76,-1)
screen_SPD_Int_1.set_size(24,47)
screen_SPD_Int_1.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp1166320099.png','rb') as f:
        screen_SPD_Int_1_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp1166320099.png')
    sys.exit()

screen_SPD_Int_1_img = lv.img_dsc_t({
  'data_size': len(screen_SPD_Int_1_img_data),
  'header': {'always_zero': 0, 'w': 24, 'h': 47, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_SPD_Int_1_img_data
})

screen_SPD_Int_1.set_src(screen_SPD_Int_1_img)
screen_SPD_Int_1.set_pivot(0,0)
screen_SPD_Int_1.set_angle(0)
# create style style_screen_spd_int_1_main_main_default
style_screen_spd_int_1_main_main_default = lv.style_t()
style_screen_spd_int_1_main_main_default.init()
style_screen_spd_int_1_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_spd_int_1_main_main_default.set_img_recolor_opa(0)
style_screen_spd_int_1_main_main_default.set_img_opa(0)

# add style for screen_SPD_Int_1
screen_SPD_Int_1.add_style(style_screen_spd_int_1_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_SPD_Int_0 = lv.img(screen_trip_spedo_cont)
screen_SPD_Int_0.set_pos(76,-1)
screen_SPD_Int_0.set_size(24,47)
screen_SPD_Int_0.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1051437854.png','rb') as f:
        screen_SPD_Int_0_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1051437854.png')
    sys.exit()

screen_SPD_Int_0_img = lv.img_dsc_t({
  'data_size': len(screen_SPD_Int_0_img_data),
  'header': {'always_zero': 0, 'w': 24, 'h': 47, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_SPD_Int_0_img_data
})

screen_SPD_Int_0.set_src(screen_SPD_Int_0_img)
screen_SPD_Int_0.set_pivot(0,0)
screen_SPD_Int_0.set_angle(0)
# create style style_screen_spd_int_0_main_main_default
style_screen_spd_int_0_main_main_default = lv.style_t()
style_screen_spd_int_0_main_main_default.init()
style_screen_spd_int_0_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_spd_int_0_main_main_default.set_img_recolor_opa(0)
style_screen_spd_int_0_main_main_default.set_img_opa(0)

# add style for screen_SPD_Int_0
screen_SPD_Int_0.add_style(style_screen_spd_int_0_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_trip_spedo_unit = lv.label(screen_trip_spedo_cont)
screen_trip_spedo_unit.set_pos(104,34)
screen_trip_spedo_unit.set_size(28,10)
screen_trip_spedo_unit.set_text("Km/h")
screen_trip_spedo_unit.set_long_mode(lv.label.LONG.CLIP)
screen_trip_spedo_unit.set_style_text_align(lv.TEXT_ALIGN.LEFT, 0)
# create style style_screen_trip_spedo_unit_main_main_default
style_screen_trip_spedo_unit_main_main_default = lv.style_t()
style_screen_trip_spedo_unit_main_main_default.init()
style_screen_trip_spedo_unit_main_main_default.set_radius(0)
style_screen_trip_spedo_unit_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_screen_trip_spedo_unit_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_trip_spedo_unit_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_screen_trip_spedo_unit_main_main_default.set_bg_opa(0)
style_screen_trip_spedo_unit_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_screen_trip_spedo_unit_main_main_default.set_text_font(lv.font_FjallaOne_Regular_11)
except AttributeError:
    try:
        style_screen_trip_spedo_unit_main_main_default.set_text_font(lv.font_montserrat_11)
    except AttributeError:
        style_screen_trip_spedo_unit_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_trip_spedo_unit_main_main_default.set_text_letter_space(0)
style_screen_trip_spedo_unit_main_main_default.set_pad_left(0)
style_screen_trip_spedo_unit_main_main_default.set_pad_right(0)
style_screen_trip_spedo_unit_main_main_default.set_pad_top(0)
style_screen_trip_spedo_unit_main_main_default.set_pad_bottom(0)

# add style for screen_trip_spedo_unit
screen_trip_spedo_unit.add_style(style_screen_trip_spedo_unit_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_trip_spedo_line = lv.img(screen_trip_spedo_cont)
screen_trip_spedo_line.set_pos(0,61)
screen_trip_spedo_line.set_size(134,2)
screen_trip_spedo_line.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp1325776533.png','rb') as f:
        screen_trip_spedo_line_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp1325776533.png')
    sys.exit()

screen_trip_spedo_line_img = lv.img_dsc_t({
  'data_size': len(screen_trip_spedo_line_img_data),
  'header': {'always_zero': 0, 'w': 134, 'h': 2, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_trip_spedo_line_img_data
})

screen_trip_spedo_line.set_src(screen_trip_spedo_line_img)
screen_trip_spedo_line.set_pivot(0,0)
screen_trip_spedo_line.set_angle(0)
# create style style_screen_trip_spedo_line_main_main_default
style_screen_trip_spedo_line_main_main_default = lv.style_t()
style_screen_trip_spedo_line_main_main_default.init()
style_screen_trip_spedo_line_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_trip_spedo_line_main_main_default.set_img_recolor_opa(0)
style_screen_trip_spedo_line_main_main_default.set_img_opa(255)

# add style for screen_trip_spedo_line
screen_trip_spedo_line.add_style(style_screen_trip_spedo_line_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_trip_spedo_s1 = lv.img(screen_trip_spedo_cont)
screen_trip_spedo_s1.set_pos(76,-1)
screen_trip_spedo_s1.set_size(24,47)
screen_trip_spedo_s1.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1540236168.png','rb') as f:
        screen_trip_spedo_s1_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1540236168.png')
    sys.exit()

screen_trip_spedo_s1_img = lv.img_dsc_t({
  'data_size': len(screen_trip_spedo_s1_img_data),
  'header': {'always_zero': 0, 'w': 24, 'h': 47, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_trip_spedo_s1_img_data
})

screen_trip_spedo_s1.set_src(screen_trip_spedo_s1_img)
screen_trip_spedo_s1.set_pivot(0,0)
screen_trip_spedo_s1.set_angle(0)
# create style style_screen_trip_spedo_s1_main_main_default
style_screen_trip_spedo_s1_main_main_default = lv.style_t()
style_screen_trip_spedo_s1_main_main_default.init()
style_screen_trip_spedo_s1_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_trip_spedo_s1_main_main_default.set_img_recolor_opa(0)
style_screen_trip_spedo_s1_main_main_default.set_img_opa(255)

# add style for screen_trip_spedo_s1
screen_trip_spedo_s1.add_style(style_screen_trip_spedo_s1_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_trip_spedo_s2 = lv.img(screen_trip_spedo_cont)
screen_trip_spedo_s2.set_pos(46,-1)
screen_trip_spedo_s2.set_size(24,47)
screen_trip_spedo_s2.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1540236168.png','rb') as f:
        screen_trip_spedo_s2_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1540236168.png')
    sys.exit()

screen_trip_spedo_s2_img = lv.img_dsc_t({
  'data_size': len(screen_trip_spedo_s2_img_data),
  'header': {'always_zero': 0, 'w': 24, 'h': 47, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_trip_spedo_s2_img_data
})

screen_trip_spedo_s2.set_src(screen_trip_spedo_s2_img)
screen_trip_spedo_s2.set_pivot(0,0)
screen_trip_spedo_s2.set_angle(0)
# create style style_screen_trip_spedo_s2_main_main_default
style_screen_trip_spedo_s2_main_main_default = lv.style_t()
style_screen_trip_spedo_s2_main_main_default.init()
style_screen_trip_spedo_s2_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_trip_spedo_s2_main_main_default.set_img_recolor_opa(0)
style_screen_trip_spedo_s2_main_main_default.set_img_opa(255)

# add style for screen_trip_spedo_s2
screen_trip_spedo_s2.add_style(style_screen_trip_spedo_s2_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_trip_spedo_s3 = lv.img(screen_trip_spedo_cont)
screen_trip_spedo_s3.set_pos(17,-1)
screen_trip_spedo_s3.set_size(24,47)
screen_trip_spedo_s3.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-2021486978.png','rb') as f:
        screen_trip_spedo_s3_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-2021486978.png')
    sys.exit()

screen_trip_spedo_s3_img = lv.img_dsc_t({
  'data_size': len(screen_trip_spedo_s3_img_data),
  'header': {'always_zero': 0, 'w': 24, 'h': 47, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_trip_spedo_s3_img_data
})

screen_trip_spedo_s3.set_src(screen_trip_spedo_s3_img)
screen_trip_spedo_s3.set_pivot(0,0)
screen_trip_spedo_s3.set_angle(0)
# create style style_screen_trip_spedo_s3_main_main_default
style_screen_trip_spedo_s3_main_main_default = lv.style_t()
style_screen_trip_spedo_s3_main_main_default.init()
style_screen_trip_spedo_s3_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_trip_spedo_s3_main_main_default.set_img_recolor_opa(0)
style_screen_trip_spedo_s3_main_main_default.set_img_opa(255)

# add style for screen_trip_spedo_s3
screen_trip_spedo_s3.add_style(style_screen_trip_spedo_s3_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_screen_trip_spedo_cont_main_main_default
style_screen_trip_spedo_cont_main_main_default = lv.style_t()
style_screen_trip_spedo_cont_main_main_default.init()
style_screen_trip_spedo_cont_main_main_default.set_radius(0)
style_screen_trip_spedo_cont_main_main_default.set_bg_color(lv.color_make(0x00,0x00,0x00))
style_screen_trip_spedo_cont_main_main_default.set_bg_grad_color(lv.color_make(0x00,0x00,0x00))
style_screen_trip_spedo_cont_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_screen_trip_spedo_cont_main_main_default.set_bg_opa(255)
style_screen_trip_spedo_cont_main_main_default.set_border_color(lv.color_make(0x00,0x00,0x00))
style_screen_trip_spedo_cont_main_main_default.set_border_width(0)
style_screen_trip_spedo_cont_main_main_default.set_border_opa(255)
style_screen_trip_spedo_cont_main_main_default.set_pad_left(0)
style_screen_trip_spedo_cont_main_main_default.set_pad_right(0)
style_screen_trip_spedo_cont_main_main_default.set_pad_top(0)
style_screen_trip_spedo_cont_main_main_default.set_pad_bottom(0)

# add style for screen_trip_spedo_cont
screen_trip_spedo_cont.add_style(style_screen_trip_spedo_cont_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_Hidden_White = lv.img(screen)
screen_Hidden_White.set_pos(143,122)
screen_Hidden_White.set_size(34,69)
screen_Hidden_White.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1236585705.png','rb') as f:
        screen_Hidden_White_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1236585705.png')
    sys.exit()

screen_Hidden_White_img = lv.img_dsc_t({
  'data_size': len(screen_Hidden_White_img_data),
  'header': {'always_zero': 0, 'w': 34, 'h': 69, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_Hidden_White_img_data
})

screen_Hidden_White.set_src(screen_Hidden_White_img)
screen_Hidden_White.set_pivot(0,0)
screen_Hidden_White.set_angle(0)
# create style style_screen_hidden_white_main_main_default
style_screen_hidden_white_main_main_default = lv.style_t()
style_screen_hidden_white_main_main_default.init()
style_screen_hidden_white_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_hidden_white_main_main_default.set_img_recolor_opa(0)
style_screen_hidden_white_main_main_default.set_img_opa(0)

# add style for screen_Hidden_White
screen_Hidden_White.add_style(style_screen_hidden_white_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_Sub_Con = lv.img(screen)
screen_Sub_Con.set_pos(204,151)
screen_Sub_Con.set_size(20,20)
screen_Sub_Con.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1198168671.png','rb') as f:
        screen_Sub_Con_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1198168671.png')
    sys.exit()

screen_Sub_Con_img = lv.img_dsc_t({
  'data_size': len(screen_Sub_Con_img_data),
  'header': {'always_zero': 0, 'w': 20, 'h': 20, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_Sub_Con_img_data
})

screen_Sub_Con.set_src(screen_Sub_Con_img)
screen_Sub_Con.set_pivot(0,0)
screen_Sub_Con.set_angle(0)
# create style style_screen_sub_con_main_main_default
style_screen_sub_con_main_main_default = lv.style_t()
style_screen_sub_con_main_main_default.init()
style_screen_sub_con_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_sub_con_main_main_default.set_img_recolor_opa(0)
style_screen_sub_con_main_main_default.set_img_opa(255)

# add style for screen_Sub_Con
screen_Sub_Con.add_style(style_screen_sub_con_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

Setting_Screen = lv.obj()
# create style style_setting_screen_main_main_default
style_setting_screen_main_main_default = lv.style_t()
style_setting_screen_main_main_default.init()
style_setting_screen_main_main_default.set_bg_color(lv.color_make(0x00,0x00,0x00))
style_setting_screen_main_main_default.set_bg_opa(255)

# add style for Setting_Screen
Setting_Screen.add_style(style_setting_screen_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

Setting_Screen_skin = lv.img(Setting_Screen)
Setting_Screen_skin.set_pos(0,0)
Setting_Screen_skin.set_size(240,320)
Setting_Screen_skin.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1914181163.png','rb') as f:
        Setting_Screen_skin_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1914181163.png')
    sys.exit()

Setting_Screen_skin_img = lv.img_dsc_t({
  'data_size': len(Setting_Screen_skin_img_data),
  'header': {'always_zero': 0, 'w': 240, 'h': 320, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': Setting_Screen_skin_img_data
})

Setting_Screen_skin.set_src(Setting_Screen_skin_img)
Setting_Screen_skin.set_pivot(0,0)
Setting_Screen_skin.set_angle(0)
# create style style_setting_screen_skin_main_main_default
style_setting_screen_skin_main_main_default = lv.style_t()
style_setting_screen_skin_main_main_default.init()
style_setting_screen_skin_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_setting_screen_skin_main_main_default.set_img_recolor_opa(0)
style_setting_screen_skin_main_main_default.set_img_opa(255)

# add style for Setting_Screen_skin
Setting_Screen_skin.add_style(style_setting_screen_skin_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

Setting_Screen_D_Cir = lv.img(Setting_Screen)
Setting_Screen_D_Cir.set_pos(7,47)
Setting_Screen_D_Cir.set_size(226,226)
Setting_Screen_D_Cir.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-480540445.png','rb') as f:
        Setting_Screen_D_Cir_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-480540445.png')
    sys.exit()

Setting_Screen_D_Cir_img = lv.img_dsc_t({
  'data_size': len(Setting_Screen_D_Cir_img_data),
  'header': {'always_zero': 0, 'w': 226, 'h': 226, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': Setting_Screen_D_Cir_img_data
})

Setting_Screen_D_Cir.set_src(Setting_Screen_D_Cir_img)
Setting_Screen_D_Cir.set_pivot(0,0)
Setting_Screen_D_Cir.set_angle(0)
# create style style_setting_screen_d_cir_main_main_default
style_setting_screen_d_cir_main_main_default = lv.style_t()
style_setting_screen_d_cir_main_main_default.init()
style_setting_screen_d_cir_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_setting_screen_d_cir_main_main_default.set_img_recolor_opa(0)
style_setting_screen_d_cir_main_main_default.set_img_opa(0)

# add style for Setting_Screen_D_Cir
Setting_Screen_D_Cir.add_style(style_setting_screen_d_cir_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

Setting_Screen_FogLampTT = lv.imgbtn(Setting_Screen)
Setting_Screen_FogLampTT.set_pos(10,12)
Setting_Screen_FogLampTT.set_size(24,20)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-552738788.png','rb') as f:
        Setting_Screen_FogLampTT_imgReleased_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-552738788.png')
    sys.exit()

Setting_Screen_FogLampTT_imgReleased = lv.img_dsc_t({
  'data_size': len(Setting_Screen_FogLampTT_imgReleased_data),
  'header': {'always_zero': 0, 'w': 24, 'h': 20, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': Setting_Screen_FogLampTT_imgReleased_data
})
Setting_Screen_FogLampTT.set_src(lv.imgbtn.STATE.RELEASED, Setting_Screen_FogLampTT_imgReleased, None, None)

try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp193804431.png','rb') as f:
        Setting_Screen_FogLampTT_imgPressed_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp193804431.png')
    sys.exit()

Setting_Screen_FogLampTT_imgPressed = lv.img_dsc_t({
  'data_size': len(Setting_Screen_FogLampTT_imgPressed_data),
  'header': {'always_zero': 0, 'w': 24, 'h': 20, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': Setting_Screen_FogLampTT_imgPressed_data
})
Setting_Screen_FogLampTT.set_src(lv.imgbtn.STATE.PRESSED, Setting_Screen_FogLampTT_imgPressed, None, None)




Setting_Screen_FogLampTT.add_flag(lv.obj.FLAG.CHECKABLE)
# create style style_setting_screen_foglamptt_main_main_default
style_setting_screen_foglamptt_main_main_default = lv.style_t()
style_setting_screen_foglamptt_main_main_default.init()
style_setting_screen_foglamptt_main_main_default.set_text_color(lv.color_make(0x00,0x00,0x00))
try:
    style_setting_screen_foglamptt_main_main_default.set_text_font(lv.font_simsun_12)
except AttributeError:
    try:
        style_setting_screen_foglamptt_main_main_default.set_text_font(lv.font_montserrat_12)
    except AttributeError:
        style_setting_screen_foglamptt_main_main_default.set_text_font(lv.font_montserrat_16)
style_setting_screen_foglamptt_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_setting_screen_foglamptt_main_main_default.set_img_recolor_opa(0)
style_setting_screen_foglamptt_main_main_default.set_img_opa(255)

# add style for Setting_Screen_FogLampTT
Setting_Screen_FogLampTT.add_style(style_setting_screen_foglamptt_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_setting_screen_foglamptt_main_main_pressed
style_setting_screen_foglamptt_main_main_pressed = lv.style_t()
style_setting_screen_foglamptt_main_main_pressed.init()
style_setting_screen_foglamptt_main_main_pressed.set_text_color(lv.color_make(0xFF,0x33,0xFF))
try:
    style_setting_screen_foglamptt_main_main_pressed.set_text_font(lv.font_simsun_16)
except AttributeError:
    try:
        style_setting_screen_foglamptt_main_main_pressed.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_setting_screen_foglamptt_main_main_pressed.set_text_font(lv.font_montserrat_16)
style_setting_screen_foglamptt_main_main_pressed.set_img_recolor(lv.color_make(0x00,0x00,0x00))
style_setting_screen_foglamptt_main_main_pressed.set_img_recolor_opa(0)

# add style for Setting_Screen_FogLampTT
Setting_Screen_FogLampTT.add_style(style_setting_screen_foglamptt_main_main_pressed, lv.PART.MAIN|lv.STATE.PRESSED)

# create style style_setting_screen_foglamptt_main_main_checked
style_setting_screen_foglamptt_main_main_checked = lv.style_t()
style_setting_screen_foglamptt_main_main_checked.init()
style_setting_screen_foglamptt_main_main_checked.set_text_color(lv.color_make(0xFF,0x33,0xFF))
try:
    style_setting_screen_foglamptt_main_main_checked.set_text_font(lv.font_simsun_16)
except AttributeError:
    try:
        style_setting_screen_foglamptt_main_main_checked.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_setting_screen_foglamptt_main_main_checked.set_text_font(lv.font_montserrat_16)
style_setting_screen_foglamptt_main_main_checked.set_img_recolor(lv.color_make(0x00,0x00,0x00))
style_setting_screen_foglamptt_main_main_checked.set_img_recolor_opa(0)

# add style for Setting_Screen_FogLampTT
Setting_Screen_FogLampTT.add_style(style_setting_screen_foglamptt_main_main_checked, lv.PART.MAIN|lv.STATE.CHECKED)

Setting_Screen_imgEngineTT = lv.imgbtn(Setting_Screen)
Setting_Screen_imgEngineTT.set_pos(205,13)
Setting_Screen_imgEngineTT.set_size(25,17)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1283435164.png','rb') as f:
        Setting_Screen_imgEngineTT_imgReleased_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1283435164.png')
    sys.exit()

Setting_Screen_imgEngineTT_imgReleased = lv.img_dsc_t({
  'data_size': len(Setting_Screen_imgEngineTT_imgReleased_data),
  'header': {'always_zero': 0, 'w': 25, 'h': 17, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': Setting_Screen_imgEngineTT_imgReleased_data
})
Setting_Screen_imgEngineTT.set_src(lv.imgbtn.STATE.RELEASED, Setting_Screen_imgEngineTT_imgReleased, None, None)

try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp1229638200.png','rb') as f:
        Setting_Screen_imgEngineTT_imgPressed_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp1229638200.png')
    sys.exit()

Setting_Screen_imgEngineTT_imgPressed = lv.img_dsc_t({
  'data_size': len(Setting_Screen_imgEngineTT_imgPressed_data),
  'header': {'always_zero': 0, 'w': 25, 'h': 17, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': Setting_Screen_imgEngineTT_imgPressed_data
})
Setting_Screen_imgEngineTT.set_src(lv.imgbtn.STATE.PRESSED, Setting_Screen_imgEngineTT_imgPressed, None, None)




Setting_Screen_imgEngineTT.add_flag(lv.obj.FLAG.CHECKABLE)
# create style style_setting_screen_imgenginett_main_main_default
style_setting_screen_imgenginett_main_main_default = lv.style_t()
style_setting_screen_imgenginett_main_main_default.init()
style_setting_screen_imgenginett_main_main_default.set_text_color(lv.color_make(0x00,0x00,0x00))
try:
    style_setting_screen_imgenginett_main_main_default.set_text_font(lv.font_simsun_12)
except AttributeError:
    try:
        style_setting_screen_imgenginett_main_main_default.set_text_font(lv.font_montserrat_12)
    except AttributeError:
        style_setting_screen_imgenginett_main_main_default.set_text_font(lv.font_montserrat_16)
style_setting_screen_imgenginett_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_setting_screen_imgenginett_main_main_default.set_img_recolor_opa(0)
style_setting_screen_imgenginett_main_main_default.set_img_opa(255)

# add style for Setting_Screen_imgEngineTT
Setting_Screen_imgEngineTT.add_style(style_setting_screen_imgenginett_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_setting_screen_imgenginett_main_main_pressed
style_setting_screen_imgenginett_main_main_pressed = lv.style_t()
style_setting_screen_imgenginett_main_main_pressed.init()
style_setting_screen_imgenginett_main_main_pressed.set_text_color(lv.color_make(0xFF,0x33,0xFF))
try:
    style_setting_screen_imgenginett_main_main_pressed.set_text_font(lv.font_simsun_16)
except AttributeError:
    try:
        style_setting_screen_imgenginett_main_main_pressed.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_setting_screen_imgenginett_main_main_pressed.set_text_font(lv.font_montserrat_16)
style_setting_screen_imgenginett_main_main_pressed.set_img_recolor(lv.color_make(0x00,0x00,0x00))
style_setting_screen_imgenginett_main_main_pressed.set_img_recolor_opa(0)

# add style for Setting_Screen_imgEngineTT
Setting_Screen_imgEngineTT.add_style(style_setting_screen_imgenginett_main_main_pressed, lv.PART.MAIN|lv.STATE.PRESSED)

# create style style_setting_screen_imgenginett_main_main_checked
style_setting_screen_imgenginett_main_main_checked = lv.style_t()
style_setting_screen_imgenginett_main_main_checked.init()
style_setting_screen_imgenginett_main_main_checked.set_text_color(lv.color_make(0xFF,0x33,0xFF))
try:
    style_setting_screen_imgenginett_main_main_checked.set_text_font(lv.font_simsun_16)
except AttributeError:
    try:
        style_setting_screen_imgenginett_main_main_checked.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_setting_screen_imgenginett_main_main_checked.set_text_font(lv.font_montserrat_16)
style_setting_screen_imgenginett_main_main_checked.set_img_recolor(lv.color_make(0x00,0x00,0x00))
style_setting_screen_imgenginett_main_main_checked.set_img_recolor_opa(0)

# add style for Setting_Screen_imgEngineTT
Setting_Screen_imgEngineTT.add_style(style_setting_screen_imgenginett_main_main_checked, lv.PART.MAIN|lv.STATE.CHECKED)

Setting_Screen_imgOilTelltale = lv.imgbtn(Setting_Screen)
Setting_Screen_imgOilTelltale.set_pos(6,291)
Setting_Screen_imgOilTelltale.set_size(32,13)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp1312483137.png','rb') as f:
        Setting_Screen_imgOilTelltale_imgReleased_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp1312483137.png')
    sys.exit()

Setting_Screen_imgOilTelltale_imgReleased = lv.img_dsc_t({
  'data_size': len(Setting_Screen_imgOilTelltale_imgReleased_data),
  'header': {'always_zero': 0, 'w': 32, 'h': 13, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': Setting_Screen_imgOilTelltale_imgReleased_data
})
Setting_Screen_imgOilTelltale.set_src(lv.imgbtn.STATE.RELEASED, Setting_Screen_imgOilTelltale_imgReleased, None, None)

try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-2059009200.png','rb') as f:
        Setting_Screen_imgOilTelltale_imgPressed_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-2059009200.png')
    sys.exit()

Setting_Screen_imgOilTelltale_imgPressed = lv.img_dsc_t({
  'data_size': len(Setting_Screen_imgOilTelltale_imgPressed_data),
  'header': {'always_zero': 0, 'w': 32, 'h': 13, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': Setting_Screen_imgOilTelltale_imgPressed_data
})
Setting_Screen_imgOilTelltale.set_src(lv.imgbtn.STATE.PRESSED, Setting_Screen_imgOilTelltale_imgPressed, None, None)




Setting_Screen_imgOilTelltale.add_flag(lv.obj.FLAG.CHECKABLE)
# create style style_setting_screen_imgoiltelltale_main_main_default
style_setting_screen_imgoiltelltale_main_main_default = lv.style_t()
style_setting_screen_imgoiltelltale_main_main_default.init()
style_setting_screen_imgoiltelltale_main_main_default.set_text_color(lv.color_make(0x00,0x00,0x00))
try:
    style_setting_screen_imgoiltelltale_main_main_default.set_text_font(lv.font_simsun_12)
except AttributeError:
    try:
        style_setting_screen_imgoiltelltale_main_main_default.set_text_font(lv.font_montserrat_12)
    except AttributeError:
        style_setting_screen_imgoiltelltale_main_main_default.set_text_font(lv.font_montserrat_16)
style_setting_screen_imgoiltelltale_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_setting_screen_imgoiltelltale_main_main_default.set_img_recolor_opa(0)
style_setting_screen_imgoiltelltale_main_main_default.set_img_opa(255)

# add style for Setting_Screen_imgOilTelltale
Setting_Screen_imgOilTelltale.add_style(style_setting_screen_imgoiltelltale_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_setting_screen_imgoiltelltale_main_main_pressed
style_setting_screen_imgoiltelltale_main_main_pressed = lv.style_t()
style_setting_screen_imgoiltelltale_main_main_pressed.init()
style_setting_screen_imgoiltelltale_main_main_pressed.set_text_color(lv.color_make(0xFF,0x33,0xFF))
try:
    style_setting_screen_imgoiltelltale_main_main_pressed.set_text_font(lv.font_simsun_16)
except AttributeError:
    try:
        style_setting_screen_imgoiltelltale_main_main_pressed.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_setting_screen_imgoiltelltale_main_main_pressed.set_text_font(lv.font_montserrat_16)
style_setting_screen_imgoiltelltale_main_main_pressed.set_img_recolor(lv.color_make(0x00,0x00,0x00))
style_setting_screen_imgoiltelltale_main_main_pressed.set_img_recolor_opa(0)

# add style for Setting_Screen_imgOilTelltale
Setting_Screen_imgOilTelltale.add_style(style_setting_screen_imgoiltelltale_main_main_pressed, lv.PART.MAIN|lv.STATE.PRESSED)

# create style style_setting_screen_imgoiltelltale_main_main_checked
style_setting_screen_imgoiltelltale_main_main_checked = lv.style_t()
style_setting_screen_imgoiltelltale_main_main_checked.init()
style_setting_screen_imgoiltelltale_main_main_checked.set_text_color(lv.color_make(0xFF,0x33,0xFF))
try:
    style_setting_screen_imgoiltelltale_main_main_checked.set_text_font(lv.font_simsun_16)
except AttributeError:
    try:
        style_setting_screen_imgoiltelltale_main_main_checked.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_setting_screen_imgoiltelltale_main_main_checked.set_text_font(lv.font_montserrat_16)
style_setting_screen_imgoiltelltale_main_main_checked.set_img_recolor(lv.color_make(0x00,0x00,0x00))
style_setting_screen_imgoiltelltale_main_main_checked.set_img_recolor_opa(0)

# add style for Setting_Screen_imgOilTelltale
Setting_Screen_imgOilTelltale.add_style(style_setting_screen_imgoiltelltale_main_main_checked, lv.PART.MAIN|lv.STATE.CHECKED)

Setting_Screen_Clock_hour = lv.label(Setting_Screen)
Setting_Screen_Clock_hour.set_pos(75,285)
Setting_Screen_Clock_hour.set_size(21,15)
Setting_Screen_Clock_hour.set_text("24")
Setting_Screen_Clock_hour.set_long_mode(lv.label.LONG.WRAP)
Setting_Screen_Clock_hour.set_style_text_align(lv.TEXT_ALIGN.RIGHT, 0)
# create style style_setting_screen_clock_hour_main_main_default
style_setting_screen_clock_hour_main_main_default = lv.style_t()
style_setting_screen_clock_hour_main_main_default.init()
style_setting_screen_clock_hour_main_main_default.set_radius(0)
style_setting_screen_clock_hour_main_main_default.set_bg_color(lv.color_make(0x00,0x00,0x00))
style_setting_screen_clock_hour_main_main_default.set_bg_grad_color(lv.color_make(0x00,0x00,0x00))
style_setting_screen_clock_hour_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_setting_screen_clock_hour_main_main_default.set_bg_opa(0)
style_setting_screen_clock_hour_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_setting_screen_clock_hour_main_main_default.set_text_font(lv.font_FjallaOne_Regular_14)
except AttributeError:
    try:
        style_setting_screen_clock_hour_main_main_default.set_text_font(lv.font_montserrat_14)
    except AttributeError:
        style_setting_screen_clock_hour_main_main_default.set_text_font(lv.font_montserrat_16)
style_setting_screen_clock_hour_main_main_default.set_text_letter_space(0)
style_setting_screen_clock_hour_main_main_default.set_pad_left(0)
style_setting_screen_clock_hour_main_main_default.set_pad_right(0)
style_setting_screen_clock_hour_main_main_default.set_pad_top(0)
style_setting_screen_clock_hour_main_main_default.set_pad_bottom(0)

# add style for Setting_Screen_Clock_hour
Setting_Screen_Clock_hour.add_style(style_setting_screen_clock_hour_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

Setting_Screen_Clock_min = lv.label(Setting_Screen)
Setting_Screen_Clock_min.set_pos(107,285)
Setting_Screen_Clock_min.set_size(20,15)
Setting_Screen_Clock_min.set_text("60")
Setting_Screen_Clock_min.set_long_mode(lv.label.LONG.WRAP)
Setting_Screen_Clock_min.set_style_text_align(lv.TEXT_ALIGN.LEFT, 0)
# create style style_setting_screen_clock_min_main_main_default
style_setting_screen_clock_min_main_main_default = lv.style_t()
style_setting_screen_clock_min_main_main_default.init()
style_setting_screen_clock_min_main_main_default.set_radius(0)
style_setting_screen_clock_min_main_main_default.set_bg_color(lv.color_make(0x00,0x00,0x00))
style_setting_screen_clock_min_main_main_default.set_bg_grad_color(lv.color_make(0x00,0x00,0x00))
style_setting_screen_clock_min_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_setting_screen_clock_min_main_main_default.set_bg_opa(0)
style_setting_screen_clock_min_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_setting_screen_clock_min_main_main_default.set_text_font(lv.font_FjallaOne_Regular_14)
except AttributeError:
    try:
        style_setting_screen_clock_min_main_main_default.set_text_font(lv.font_montserrat_14)
    except AttributeError:
        style_setting_screen_clock_min_main_main_default.set_text_font(lv.font_montserrat_16)
style_setting_screen_clock_min_main_main_default.set_text_letter_space(0)
style_setting_screen_clock_min_main_main_default.set_pad_left(0)
style_setting_screen_clock_min_main_main_default.set_pad_right(0)
style_setting_screen_clock_min_main_main_default.set_pad_top(0)
style_setting_screen_clock_min_main_main_default.set_pad_bottom(0)

# add style for Setting_Screen_Clock_min
Setting_Screen_Clock_min.add_style(style_setting_screen_clock_min_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

Setting_Screen_Clock_Colan = lv.label(Setting_Screen)
Setting_Screen_Clock_Colan.set_pos(94,285)
Setting_Screen_Clock_Colan.set_size(15,15)
Setting_Screen_Clock_Colan.set_text(":")
Setting_Screen_Clock_Colan.set_long_mode(lv.label.LONG.WRAP)
Setting_Screen_Clock_Colan.set_style_text_align(lv.TEXT_ALIGN.CENTER, 0)
# create style style_setting_screen_clock_colan_main_main_default
style_setting_screen_clock_colan_main_main_default = lv.style_t()
style_setting_screen_clock_colan_main_main_default.init()
style_setting_screen_clock_colan_main_main_default.set_radius(0)
style_setting_screen_clock_colan_main_main_default.set_bg_color(lv.color_make(0x00,0x00,0x00))
style_setting_screen_clock_colan_main_main_default.set_bg_grad_color(lv.color_make(0x00,0x00,0x00))
style_setting_screen_clock_colan_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_setting_screen_clock_colan_main_main_default.set_bg_opa(0)
style_setting_screen_clock_colan_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_setting_screen_clock_colan_main_main_default.set_text_font(lv.font_FjallaOne_Regular_14)
except AttributeError:
    try:
        style_setting_screen_clock_colan_main_main_default.set_text_font(lv.font_montserrat_14)
    except AttributeError:
        style_setting_screen_clock_colan_main_main_default.set_text_font(lv.font_montserrat_16)
style_setting_screen_clock_colan_main_main_default.set_text_letter_space(2)
style_setting_screen_clock_colan_main_main_default.set_pad_left(0)
style_setting_screen_clock_colan_main_main_default.set_pad_right(0)
style_setting_screen_clock_colan_main_main_default.set_pad_top(0)
style_setting_screen_clock_colan_main_main_default.set_pad_bottom(0)

# add style for Setting_Screen_Clock_Colan
Setting_Screen_Clock_Colan.add_style(style_setting_screen_clock_colan_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

Setting_Screen_Sub_Button = lv.imgbtn(Setting_Screen)
Setting_Screen_Sub_Button.set_pos(201,152)
Setting_Screen_Sub_Button.set_size(20,20)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp517217360.png','rb') as f:
        Setting_Screen_Sub_Button_imgReleased_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp517217360.png')
    sys.exit()

Setting_Screen_Sub_Button_imgReleased = lv.img_dsc_t({
  'data_size': len(Setting_Screen_Sub_Button_imgReleased_data),
  'header': {'always_zero': 0, 'w': 20, 'h': 20, 'cf': lv.img.CF.TRUE_COLOR},
  'data': Setting_Screen_Sub_Button_imgReleased_data
})
Setting_Screen_Sub_Button.set_src(lv.imgbtn.STATE.RELEASED, Setting_Screen_Sub_Button_imgReleased, None, None)

try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-149151814.png','rb') as f:
        Setting_Screen_Sub_Button_imgPressed_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-149151814.png')
    sys.exit()

Setting_Screen_Sub_Button_imgPressed = lv.img_dsc_t({
  'data_size': len(Setting_Screen_Sub_Button_imgPressed_data),
  'header': {'always_zero': 0, 'w': 20, 'h': 20, 'cf': lv.img.CF.TRUE_COLOR},
  'data': Setting_Screen_Sub_Button_imgPressed_data
})
Setting_Screen_Sub_Button.set_src(lv.imgbtn.STATE.PRESSED, Setting_Screen_Sub_Button_imgPressed, None, None)




Setting_Screen_Sub_Button.add_flag(lv.obj.FLAG.CHECKABLE)
# create style style_setting_screen_sub_button_main_main_default
style_setting_screen_sub_button_main_main_default = lv.style_t()
style_setting_screen_sub_button_main_main_default.init()
style_setting_screen_sub_button_main_main_default.set_text_color(lv.color_make(0x00,0x00,0x00))
try:
    style_setting_screen_sub_button_main_main_default.set_text_font(lv.font_simsun_12)
except AttributeError:
    try:
        style_setting_screen_sub_button_main_main_default.set_text_font(lv.font_montserrat_12)
    except AttributeError:
        style_setting_screen_sub_button_main_main_default.set_text_font(lv.font_montserrat_16)
style_setting_screen_sub_button_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_setting_screen_sub_button_main_main_default.set_img_recolor_opa(0)
style_setting_screen_sub_button_main_main_default.set_img_opa(255)

# add style for Setting_Screen_Sub_Button
Setting_Screen_Sub_Button.add_style(style_setting_screen_sub_button_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_setting_screen_sub_button_main_main_pressed
style_setting_screen_sub_button_main_main_pressed = lv.style_t()
style_setting_screen_sub_button_main_main_pressed.init()
style_setting_screen_sub_button_main_main_pressed.set_text_color(lv.color_make(0xFF,0x33,0xFF))
try:
    style_setting_screen_sub_button_main_main_pressed.set_text_font(lv.font_simsun_16)
except AttributeError:
    try:
        style_setting_screen_sub_button_main_main_pressed.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_setting_screen_sub_button_main_main_pressed.set_text_font(lv.font_montserrat_16)
style_setting_screen_sub_button_main_main_pressed.set_img_recolor(lv.color_make(0x00,0x00,0x00))
style_setting_screen_sub_button_main_main_pressed.set_img_recolor_opa(0)

# add style for Setting_Screen_Sub_Button
Setting_Screen_Sub_Button.add_style(style_setting_screen_sub_button_main_main_pressed, lv.PART.MAIN|lv.STATE.PRESSED)

# create style style_setting_screen_sub_button_main_main_checked
style_setting_screen_sub_button_main_main_checked = lv.style_t()
style_setting_screen_sub_button_main_main_checked.init()
style_setting_screen_sub_button_main_main_checked.set_text_color(lv.color_make(0xFF,0x33,0xFF))
try:
    style_setting_screen_sub_button_main_main_checked.set_text_font(lv.font_simsun_16)
except AttributeError:
    try:
        style_setting_screen_sub_button_main_main_checked.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_setting_screen_sub_button_main_main_checked.set_text_font(lv.font_montserrat_16)
style_setting_screen_sub_button_main_main_checked.set_img_recolor(lv.color_make(0x00,0x00,0x00))
style_setting_screen_sub_button_main_main_checked.set_img_recolor_opa(0)

# add style for Setting_Screen_Sub_Button
Setting_Screen_Sub_Button.add_style(style_setting_screen_sub_button_main_main_checked, lv.PART.MAIN|lv.STATE.CHECKED)

Setting_Screen_Trip_Up_Arrow = lv.imgbtn(Setting_Screen)
Setting_Screen_Trip_Up_Arrow.set_pos(110,65)
Setting_Screen_Trip_Up_Arrow.set_size(20,11)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-566102860.png','rb') as f:
        Setting_Screen_Trip_Up_Arrow_imgReleased_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-566102860.png')
    sys.exit()

Setting_Screen_Trip_Up_Arrow_imgReleased = lv.img_dsc_t({
  'data_size': len(Setting_Screen_Trip_Up_Arrow_imgReleased_data),
  'header': {'always_zero': 0, 'w': 20, 'h': 11, 'cf': lv.img.CF.TRUE_COLOR},
  'data': Setting_Screen_Trip_Up_Arrow_imgReleased_data
})
Setting_Screen_Trip_Up_Arrow.set_src(lv.imgbtn.STATE.RELEASED, Setting_Screen_Trip_Up_Arrow_imgReleased, None, None)

try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-2075185892.png','rb') as f:
        Setting_Screen_Trip_Up_Arrow_imgPressed_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-2075185892.png')
    sys.exit()

Setting_Screen_Trip_Up_Arrow_imgPressed = lv.img_dsc_t({
  'data_size': len(Setting_Screen_Trip_Up_Arrow_imgPressed_data),
  'header': {'always_zero': 0, 'w': 20, 'h': 11, 'cf': lv.img.CF.TRUE_COLOR},
  'data': Setting_Screen_Trip_Up_Arrow_imgPressed_data
})
Setting_Screen_Trip_Up_Arrow.set_src(lv.imgbtn.STATE.PRESSED, Setting_Screen_Trip_Up_Arrow_imgPressed, None, None)




Setting_Screen_Trip_Up_Arrow.add_flag(lv.obj.FLAG.CHECKABLE)
# create style style_setting_screen_trip_up_arrow_main_main_default
style_setting_screen_trip_up_arrow_main_main_default = lv.style_t()
style_setting_screen_trip_up_arrow_main_main_default.init()
style_setting_screen_trip_up_arrow_main_main_default.set_text_color(lv.color_make(0x00,0x00,0x00))
try:
    style_setting_screen_trip_up_arrow_main_main_default.set_text_font(lv.font_simsun_94)
except AttributeError:
    try:
        style_setting_screen_trip_up_arrow_main_main_default.set_text_font(lv.font_montserrat_94)
    except AttributeError:
        style_setting_screen_trip_up_arrow_main_main_default.set_text_font(lv.font_montserrat_16)
style_setting_screen_trip_up_arrow_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_setting_screen_trip_up_arrow_main_main_default.set_img_recolor_opa(0)
style_setting_screen_trip_up_arrow_main_main_default.set_img_opa(255)

# add style for Setting_Screen_Trip_Up_Arrow
Setting_Screen_Trip_Up_Arrow.add_style(style_setting_screen_trip_up_arrow_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_setting_screen_trip_up_arrow_main_main_pressed
style_setting_screen_trip_up_arrow_main_main_pressed = lv.style_t()
style_setting_screen_trip_up_arrow_main_main_pressed.init()
style_setting_screen_trip_up_arrow_main_main_pressed.set_text_color(lv.color_make(0xFF,0x33,0xFF))
try:
    style_setting_screen_trip_up_arrow_main_main_pressed.set_text_font(lv.font_simsun_16)
except AttributeError:
    try:
        style_setting_screen_trip_up_arrow_main_main_pressed.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_setting_screen_trip_up_arrow_main_main_pressed.set_text_font(lv.font_montserrat_16)
style_setting_screen_trip_up_arrow_main_main_pressed.set_img_recolor(lv.color_make(0x00,0x00,0x00))
style_setting_screen_trip_up_arrow_main_main_pressed.set_img_recolor_opa(0)

# add style for Setting_Screen_Trip_Up_Arrow
Setting_Screen_Trip_Up_Arrow.add_style(style_setting_screen_trip_up_arrow_main_main_pressed, lv.PART.MAIN|lv.STATE.PRESSED)

# create style style_setting_screen_trip_up_arrow_main_main_checked
style_setting_screen_trip_up_arrow_main_main_checked = lv.style_t()
style_setting_screen_trip_up_arrow_main_main_checked.init()
style_setting_screen_trip_up_arrow_main_main_checked.set_text_color(lv.color_make(0xFF,0x33,0xFF))
try:
    style_setting_screen_trip_up_arrow_main_main_checked.set_text_font(lv.font_simsun_16)
except AttributeError:
    try:
        style_setting_screen_trip_up_arrow_main_main_checked.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_setting_screen_trip_up_arrow_main_main_checked.set_text_font(lv.font_montserrat_16)
style_setting_screen_trip_up_arrow_main_main_checked.set_img_recolor(lv.color_make(0x00,0x00,0x00))
style_setting_screen_trip_up_arrow_main_main_checked.set_img_recolor_opa(0)

# add style for Setting_Screen_Trip_Up_Arrow
Setting_Screen_Trip_Up_Arrow.add_style(style_setting_screen_trip_up_arrow_main_main_checked, lv.PART.MAIN|lv.STATE.CHECKED)

Setting_Screen_Trip_Down_Arrow = lv.imgbtn(Setting_Screen)
Setting_Screen_Trip_Down_Arrow.set_pos(110,238)
Setting_Screen_Trip_Down_Arrow.set_size(20,11)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp1772617615.png','rb') as f:
        Setting_Screen_Trip_Down_Arrow_imgReleased_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp1772617615.png')
    sys.exit()

Setting_Screen_Trip_Down_Arrow_imgReleased = lv.img_dsc_t({
  'data_size': len(Setting_Screen_Trip_Down_Arrow_imgReleased_data),
  'header': {'always_zero': 0, 'w': 20, 'h': 11, 'cf': lv.img.CF.TRUE_COLOR},
  'data': Setting_Screen_Trip_Down_Arrow_imgReleased_data
})
Setting_Screen_Trip_Down_Arrow.set_src(lv.imgbtn.STATE.RELEASED, Setting_Screen_Trip_Down_Arrow_imgReleased, None, None)

try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-2075185892.png','rb') as f:
        Setting_Screen_Trip_Down_Arrow_imgPressed_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-2075185892.png')
    sys.exit()

Setting_Screen_Trip_Down_Arrow_imgPressed = lv.img_dsc_t({
  'data_size': len(Setting_Screen_Trip_Down_Arrow_imgPressed_data),
  'header': {'always_zero': 0, 'w': 20, 'h': 11, 'cf': lv.img.CF.TRUE_COLOR},
  'data': Setting_Screen_Trip_Down_Arrow_imgPressed_data
})
Setting_Screen_Trip_Down_Arrow.set_src(lv.imgbtn.STATE.PRESSED, Setting_Screen_Trip_Down_Arrow_imgPressed, None, None)




Setting_Screen_Trip_Down_Arrow.add_flag(lv.obj.FLAG.CHECKABLE)
# create style style_setting_screen_trip_down_arrow_main_main_default
style_setting_screen_trip_down_arrow_main_main_default = lv.style_t()
style_setting_screen_trip_down_arrow_main_main_default.init()
style_setting_screen_trip_down_arrow_main_main_default.set_text_color(lv.color_make(0x00,0x00,0x00))
try:
    style_setting_screen_trip_down_arrow_main_main_default.set_text_font(lv.font_simsun_12)
except AttributeError:
    try:
        style_setting_screen_trip_down_arrow_main_main_default.set_text_font(lv.font_montserrat_12)
    except AttributeError:
        style_setting_screen_trip_down_arrow_main_main_default.set_text_font(lv.font_montserrat_16)
style_setting_screen_trip_down_arrow_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_setting_screen_trip_down_arrow_main_main_default.set_img_recolor_opa(0)
style_setting_screen_trip_down_arrow_main_main_default.set_img_opa(255)

# add style for Setting_Screen_Trip_Down_Arrow
Setting_Screen_Trip_Down_Arrow.add_style(style_setting_screen_trip_down_arrow_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_setting_screen_trip_down_arrow_main_main_pressed
style_setting_screen_trip_down_arrow_main_main_pressed = lv.style_t()
style_setting_screen_trip_down_arrow_main_main_pressed.init()
style_setting_screen_trip_down_arrow_main_main_pressed.set_text_color(lv.color_make(0xFF,0x33,0xFF))
try:
    style_setting_screen_trip_down_arrow_main_main_pressed.set_text_font(lv.font_simsun_16)
except AttributeError:
    try:
        style_setting_screen_trip_down_arrow_main_main_pressed.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_setting_screen_trip_down_arrow_main_main_pressed.set_text_font(lv.font_montserrat_16)
style_setting_screen_trip_down_arrow_main_main_pressed.set_img_recolor(lv.color_make(0x00,0x00,0x00))
style_setting_screen_trip_down_arrow_main_main_pressed.set_img_recolor_opa(0)

# add style for Setting_Screen_Trip_Down_Arrow
Setting_Screen_Trip_Down_Arrow.add_style(style_setting_screen_trip_down_arrow_main_main_pressed, lv.PART.MAIN|lv.STATE.PRESSED)

# create style style_setting_screen_trip_down_arrow_main_main_checked
style_setting_screen_trip_down_arrow_main_main_checked = lv.style_t()
style_setting_screen_trip_down_arrow_main_main_checked.init()
style_setting_screen_trip_down_arrow_main_main_checked.set_text_color(lv.color_make(0xFF,0x33,0xFF))
try:
    style_setting_screen_trip_down_arrow_main_main_checked.set_text_font(lv.font_simsun_16)
except AttributeError:
    try:
        style_setting_screen_trip_down_arrow_main_main_checked.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_setting_screen_trip_down_arrow_main_main_checked.set_text_font(lv.font_montserrat_16)
style_setting_screen_trip_down_arrow_main_main_checked.set_img_recolor(lv.color_make(0x00,0x00,0x00))
style_setting_screen_trip_down_arrow_main_main_checked.set_img_recolor_opa(0)

# add style for Setting_Screen_Trip_Down_Arrow
Setting_Screen_Trip_Down_Arrow.add_style(style_setting_screen_trip_down_arrow_main_main_checked, lv.PART.MAIN|lv.STATE.CHECKED)

Setting_Screen_Black = lv.img(Setting_Screen)
Setting_Screen_Black.set_pos(42,99)
Setting_Screen_Black.set_size(10,16)
Setting_Screen_Black.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp212544787.png','rb') as f:
        Setting_Screen_Black_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp212544787.png')
    sys.exit()

Setting_Screen_Black_img = lv.img_dsc_t({
  'data_size': len(Setting_Screen_Black_img_data),
  'header': {'always_zero': 0, 'w': 10, 'h': 16, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': Setting_Screen_Black_img_data
})

Setting_Screen_Black.set_src(Setting_Screen_Black_img)
Setting_Screen_Black.set_pivot(0,0)
Setting_Screen_Black.set_angle(0)
# create style style_setting_screen_black_main_main_default
style_setting_screen_black_main_main_default = lv.style_t()
style_setting_screen_black_main_main_default.init()
style_setting_screen_black_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_setting_screen_black_main_main_default.set_img_recolor_opa(0)
style_setting_screen_black_main_main_default.set_img_opa(255)

# add style for Setting_Screen_Black
Setting_Screen_Black.add_style(style_setting_screen_black_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

Setting_Screen_Setting_Blank = lv.img(Setting_Screen)
Setting_Screen_Setting_Blank.set_pos(44,103)
Setting_Screen_Setting_Blank.set_size(6,13)
Setting_Screen_Setting_Blank.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp1417808499.png','rb') as f:
        Setting_Screen_Setting_Blank_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp1417808499.png')
    sys.exit()

Setting_Screen_Setting_Blank_img = lv.img_dsc_t({
  'data_size': len(Setting_Screen_Setting_Blank_img_data),
  'header': {'always_zero': 0, 'w': 6, 'h': 13, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': Setting_Screen_Setting_Blank_img_data
})

Setting_Screen_Setting_Blank.set_src(Setting_Screen_Setting_Blank_img)
Setting_Screen_Setting_Blank.set_pivot(0,0)
Setting_Screen_Setting_Blank.set_angle(0)
# create style style_setting_screen_setting_blank_main_main_default
style_setting_screen_setting_blank_main_main_default = lv.style_t()
style_setting_screen_setting_blank_main_main_default.init()
style_setting_screen_setting_blank_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_setting_screen_setting_blank_main_main_default.set_img_recolor_opa(0)
style_setting_screen_setting_blank_main_main_default.set_img_opa(255)

# add style for Setting_Screen_Setting_Blank
Setting_Screen_Setting_Blank.add_style(style_setting_screen_setting_blank_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

Setting_Screen_label_Dispaly = lv.label(Setting_Screen)
Setting_Screen_label_Dispaly.set_pos(61,22)
Setting_Screen_label_Dispaly.set_size(110,16)
Setting_Screen_label_Dispaly.set_text("SET TIN G")
Setting_Screen_label_Dispaly.set_long_mode(lv.label.LONG.CLIP)
Setting_Screen_label_Dispaly.set_style_text_align(lv.TEXT_ALIGN.CENTER, 0)
# create style style_setting_screen_label_dispaly_main_main_default
style_setting_screen_label_dispaly_main_main_default = lv.style_t()
style_setting_screen_label_dispaly_main_main_default.init()
style_setting_screen_label_dispaly_main_main_default.set_radius(0)
style_setting_screen_label_dispaly_main_main_default.set_bg_color(lv.color_make(0x00,0x00,0x00))
style_setting_screen_label_dispaly_main_main_default.set_bg_grad_color(lv.color_make(0x00,0x00,0x00))
style_setting_screen_label_dispaly_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_setting_screen_label_dispaly_main_main_default.set_bg_opa(0)
style_setting_screen_label_dispaly_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_setting_screen_label_dispaly_main_main_default.set_text_font(lv.font_FjallaOne_Regular_19)
except AttributeError:
    try:
        style_setting_screen_label_dispaly_main_main_default.set_text_font(lv.font_montserrat_19)
    except AttributeError:
        style_setting_screen_label_dispaly_main_main_default.set_text_font(lv.font_montserrat_16)
style_setting_screen_label_dispaly_main_main_default.set_text_letter_space(0)
style_setting_screen_label_dispaly_main_main_default.set_pad_left(0)
style_setting_screen_label_dispaly_main_main_default.set_pad_right(0)
style_setting_screen_label_dispaly_main_main_default.set_pad_top(0)
style_setting_screen_label_dispaly_main_main_default.set_pad_bottom(0)

# add style for Setting_Screen_label_Dispaly
Setting_Screen_label_Dispaly.add_style(style_setting_screen_label_dispaly_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

Setting_Screen_About_Label = lv.label(Setting_Screen)
Setting_Screen_About_Label.set_pos(61,101)
Setting_Screen_About_Label.set_size(131,18)
Setting_Screen_About_Label.set_text("AB OUT")
Setting_Screen_About_Label.set_long_mode(lv.label.LONG.CLIP)
Setting_Screen_About_Label.set_style_text_align(lv.TEXT_ALIGN.CENTER, 0)
# create style style_setting_screen_about_label_main_main_default
style_setting_screen_about_label_main_main_default = lv.style_t()
style_setting_screen_about_label_main_main_default.init()
style_setting_screen_about_label_main_main_default.set_radius(0)
style_setting_screen_about_label_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_setting_screen_about_label_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_setting_screen_about_label_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_setting_screen_about_label_main_main_default.set_bg_opa(0)
style_setting_screen_about_label_main_main_default.set_text_color(lv.color_make(0x4d,0x47,0x47))
try:
    style_setting_screen_about_label_main_main_default.set_text_font(lv.font_FjallaOne_Regular_22)
except AttributeError:
    try:
        style_setting_screen_about_label_main_main_default.set_text_font(lv.font_montserrat_22)
    except AttributeError:
        style_setting_screen_about_label_main_main_default.set_text_font(lv.font_montserrat_16)
style_setting_screen_about_label_main_main_default.set_text_letter_space(0)
style_setting_screen_about_label_main_main_default.set_pad_left(0)
style_setting_screen_about_label_main_main_default.set_pad_right(0)
style_setting_screen_about_label_main_main_default.set_pad_top(0)
style_setting_screen_about_label_main_main_default.set_pad_bottom(0)

# add style for Setting_Screen_About_Label
Setting_Screen_About_Label.add_style(style_setting_screen_about_label_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

Setting_Screen_Connectivity_Label = lv.label(Setting_Screen)
Setting_Screen_Connectivity_Label.set_pos(57,148)
Setting_Screen_Connectivity_Label.set_size(132,18)
Setting_Screen_Connectivity_Label.set_text("TO RESET")
Setting_Screen_Connectivity_Label.set_long_mode(lv.label.LONG.CLIP)
Setting_Screen_Connectivity_Label.set_style_text_align(lv.TEXT_ALIGN.CENTER, 0)
# create style style_setting_screen_connectivity_label_main_main_default
style_setting_screen_connectivity_label_main_main_default = lv.style_t()
style_setting_screen_connectivity_label_main_main_default.init()
style_setting_screen_connectivity_label_main_main_default.set_radius(0)
style_setting_screen_connectivity_label_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_setting_screen_connectivity_label_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_setting_screen_connectivity_label_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_setting_screen_connectivity_label_main_main_default.set_bg_opa(0)
style_setting_screen_connectivity_label_main_main_default.set_text_color(lv.color_make(0xf6,0xf4,0xf4))
try:
    style_setting_screen_connectivity_label_main_main_default.set_text_font(lv.font_FjallaOne_Regular_22)
except AttributeError:
    try:
        style_setting_screen_connectivity_label_main_main_default.set_text_font(lv.font_montserrat_22)
    except AttributeError:
        style_setting_screen_connectivity_label_main_main_default.set_text_font(lv.font_montserrat_16)
style_setting_screen_connectivity_label_main_main_default.set_text_letter_space(0)
style_setting_screen_connectivity_label_main_main_default.set_pad_left(0)
style_setting_screen_connectivity_label_main_main_default.set_pad_right(0)
style_setting_screen_connectivity_label_main_main_default.set_pad_top(0)
style_setting_screen_connectivity_label_main_main_default.set_pad_bottom(0)

# add style for Setting_Screen_Connectivity_Label
Setting_Screen_Connectivity_Label.add_style(style_setting_screen_connectivity_label_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

Setting_Screen_Bike_Label = lv.label(Setting_Screen)
Setting_Screen_Bike_Label.set_pos(54.5,196)
Setting_Screen_Bike_Label.set_size(131,18)
Setting_Screen_Bike_Label.set_text("DATE AND TIME")
Setting_Screen_Bike_Label.set_long_mode(lv.label.LONG.CLIP)
Setting_Screen_Bike_Label.set_style_text_align(lv.TEXT_ALIGN.CENTER, 0)
# create style style_setting_screen_bike_label_main_main_default
style_setting_screen_bike_label_main_main_default = lv.style_t()
style_setting_screen_bike_label_main_main_default.init()
style_setting_screen_bike_label_main_main_default.set_radius(0)
style_setting_screen_bike_label_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_setting_screen_bike_label_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_setting_screen_bike_label_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_setting_screen_bike_label_main_main_default.set_bg_opa(1)
style_setting_screen_bike_label_main_main_default.set_text_color(lv.color_make(0x46,0x44,0x44))
try:
    style_setting_screen_bike_label_main_main_default.set_text_font(lv.font_FjallaOne_Regular_22)
except AttributeError:
    try:
        style_setting_screen_bike_label_main_main_default.set_text_font(lv.font_montserrat_22)
    except AttributeError:
        style_setting_screen_bike_label_main_main_default.set_text_font(lv.font_montserrat_16)
style_setting_screen_bike_label_main_main_default.set_text_letter_space(0)
style_setting_screen_bike_label_main_main_default.set_pad_left(0)
style_setting_screen_bike_label_main_main_default.set_pad_right(0)
style_setting_screen_bike_label_main_main_default.set_pad_top(0)
style_setting_screen_bike_label_main_main_default.set_pad_bottom(0)

# add style for Setting_Screen_Bike_Label
Setting_Screen_Bike_Label.add_style(style_setting_screen_bike_label_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

Setting_Screen_Battery_Icon = lv.img(Setting_Screen)
Setting_Screen_Battery_Icon.set_pos(14,143)
Setting_Screen_Battery_Icon.set_size(30,30)
Setting_Screen_Battery_Icon.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp1056382715.png','rb') as f:
        Setting_Screen_Battery_Icon_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp1056382715.png')
    sys.exit()

Setting_Screen_Battery_Icon_img = lv.img_dsc_t({
  'data_size': len(Setting_Screen_Battery_Icon_img_data),
  'header': {'always_zero': 0, 'w': 30, 'h': 30, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': Setting_Screen_Battery_Icon_img_data
})

Setting_Screen_Battery_Icon.set_src(Setting_Screen_Battery_Icon_img)
Setting_Screen_Battery_Icon.set_pivot(0,0)
Setting_Screen_Battery_Icon.set_angle(0)
# create style style_setting_screen_battery_icon_main_main_default
style_setting_screen_battery_icon_main_main_default = lv.style_t()
style_setting_screen_battery_icon_main_main_default.init()
style_setting_screen_battery_icon_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_setting_screen_battery_icon_main_main_default.set_img_recolor_opa(0)
style_setting_screen_battery_icon_main_main_default.set_img_opa(0)

# add style for Setting_Screen_Battery_Icon
Setting_Screen_Battery_Icon.add_style(style_setting_screen_battery_icon_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

Setting_Screen_Bike_Icon = lv.img(Setting_Screen)
Setting_Screen_Bike_Icon.set_pos(14,143)
Setting_Screen_Bike_Icon.set_size(30,30)
Setting_Screen_Bike_Icon.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-502029876.png','rb') as f:
        Setting_Screen_Bike_Icon_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-502029876.png')
    sys.exit()

Setting_Screen_Bike_Icon_img = lv.img_dsc_t({
  'data_size': len(Setting_Screen_Bike_Icon_img_data),
  'header': {'always_zero': 0, 'w': 30, 'h': 30, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': Setting_Screen_Bike_Icon_img_data
})

Setting_Screen_Bike_Icon.set_src(Setting_Screen_Bike_Icon_img)
Setting_Screen_Bike_Icon.set_pivot(0,0)
Setting_Screen_Bike_Icon.set_angle(0)
# create style style_setting_screen_bike_icon_main_main_default
style_setting_screen_bike_icon_main_main_default = lv.style_t()
style_setting_screen_bike_icon_main_main_default.init()
style_setting_screen_bike_icon_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_setting_screen_bike_icon_main_main_default.set_img_recolor_opa(0)
style_setting_screen_bike_icon_main_main_default.set_img_opa(0)

# add style for Setting_Screen_Bike_Icon
Setting_Screen_Bike_Icon.add_style(style_setting_screen_bike_icon_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

Setting_Screen_Medium_Label = lv.label(Setting_Screen)
Setting_Screen_Medium_Label.set_pos(22,196)
Setting_Screen_Medium_Label.set_size(87,19)
Setting_Screen_Medium_Label.set_text("MED IUM")
Setting_Screen_Medium_Label.set_long_mode(lv.label.LONG.WRAP)
Setting_Screen_Medium_Label.set_style_text_align(lv.TEXT_ALIGN.CENTER, 0)
# create style style_setting_screen_medium_label_main_main_default
style_setting_screen_medium_label_main_main_default = lv.style_t()
style_setting_screen_medium_label_main_main_default.init()
style_setting_screen_medium_label_main_main_default.set_radius(0)
style_setting_screen_medium_label_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_setting_screen_medium_label_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_setting_screen_medium_label_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_setting_screen_medium_label_main_main_default.set_bg_opa(0)
style_setting_screen_medium_label_main_main_default.set_text_color(lv.color_make(0x56,0x4d,0x4d))
try:
    style_setting_screen_medium_label_main_main_default.set_text_font(lv.font_FjallaOne_Regular_22)
except AttributeError:
    try:
        style_setting_screen_medium_label_main_main_default.set_text_font(lv.font_montserrat_22)
    except AttributeError:
        style_setting_screen_medium_label_main_main_default.set_text_font(lv.font_montserrat_16)
style_setting_screen_medium_label_main_main_default.set_text_letter_space(0)
style_setting_screen_medium_label_main_main_default.set_pad_left(0)
style_setting_screen_medium_label_main_main_default.set_pad_right(0)
style_setting_screen_medium_label_main_main_default.set_pad_top(0)
style_setting_screen_medium_label_main_main_default.set_pad_bottom(0)

# add style for Setting_Screen_Medium_Label
Setting_Screen_Medium_Label.add_style(style_setting_screen_medium_label_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

Setting_Screen_Display_Icon = lv.img(Setting_Screen)
Setting_Screen_Display_Icon.set_pos(14,143)
Setting_Screen_Display_Icon.set_size(30,30)
Setting_Screen_Display_Icon.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1995568010.png','rb') as f:
        Setting_Screen_Display_Icon_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1995568010.png')
    sys.exit()

Setting_Screen_Display_Icon_img = lv.img_dsc_t({
  'data_size': len(Setting_Screen_Display_Icon_img_data),
  'header': {'always_zero': 0, 'w': 30, 'h': 30, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': Setting_Screen_Display_Icon_img_data
})

Setting_Screen_Display_Icon.set_src(Setting_Screen_Display_Icon_img)
Setting_Screen_Display_Icon.set_pivot(0,0)
Setting_Screen_Display_Icon.set_angle(0)
# create style style_setting_screen_display_icon_main_main_default
style_setting_screen_display_icon_main_main_default = lv.style_t()
style_setting_screen_display_icon_main_main_default.init()
style_setting_screen_display_icon_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_setting_screen_display_icon_main_main_default.set_img_recolor_opa(0)
style_setting_screen_display_icon_main_main_default.set_img_opa(255)

# add style for Setting_Screen_Display_Icon
Setting_Screen_Display_Icon.add_style(style_setting_screen_display_icon_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

Setting_Screen_Auto_Label = lv.label(Setting_Screen)
Setting_Screen_Auto_Label.set_pos(25,102)
Setting_Screen_Auto_Label.set_size(72,19)
Setting_Screen_Auto_Label.set_text("AUT O")
Setting_Screen_Auto_Label.set_long_mode(lv.label.LONG.WRAP)
Setting_Screen_Auto_Label.set_style_text_align(lv.TEXT_ALIGN.CENTER, 0)
# create style style_setting_screen_auto_label_main_main_default
style_setting_screen_auto_label_main_main_default = lv.style_t()
style_setting_screen_auto_label_main_main_default.init()
style_setting_screen_auto_label_main_main_default.set_radius(0)
style_setting_screen_auto_label_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_setting_screen_auto_label_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_setting_screen_auto_label_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_setting_screen_auto_label_main_main_default.set_bg_opa(0)
style_setting_screen_auto_label_main_main_default.set_text_color(lv.color_make(0x4c,0x43,0x43))
try:
    style_setting_screen_auto_label_main_main_default.set_text_font(lv.font_FjallaOne_Regular_22)
except AttributeError:
    try:
        style_setting_screen_auto_label_main_main_default.set_text_font(lv.font_montserrat_22)
    except AttributeError:
        style_setting_screen_auto_label_main_main_default.set_text_font(lv.font_montserrat_16)
style_setting_screen_auto_label_main_main_default.set_text_letter_space(0)
style_setting_screen_auto_label_main_main_default.set_pad_left(0)
style_setting_screen_auto_label_main_main_default.set_pad_right(0)
style_setting_screen_auto_label_main_main_default.set_pad_top(0)
style_setting_screen_auto_label_main_main_default.set_pad_bottom(0)

# add style for Setting_Screen_Auto_Label
Setting_Screen_Auto_Label.add_style(style_setting_screen_auto_label_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

Setting_Screen_Low_Labal = lv.label(Setting_Screen)
Setting_Screen_Low_Labal.set_pos(8,148)
Setting_Screen_Low_Labal.set_size(100,19)
Setting_Screen_Low_Labal.set_text("LOW")
Setting_Screen_Low_Labal.set_long_mode(lv.label.LONG.WRAP)
Setting_Screen_Low_Labal.set_style_text_align(lv.TEXT_ALIGN.CENTER, 0)
# create style style_setting_screen_low_labal_main_main_default
style_setting_screen_low_labal_main_main_default = lv.style_t()
style_setting_screen_low_labal_main_main_default.init()
style_setting_screen_low_labal_main_main_default.set_radius(0)
style_setting_screen_low_labal_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_setting_screen_low_labal_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_setting_screen_low_labal_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_setting_screen_low_labal_main_main_default.set_bg_opa(0)
style_setting_screen_low_labal_main_main_default.set_text_color(lv.color_make(0x4d,0x47,0x47))
try:
    style_setting_screen_low_labal_main_main_default.set_text_font(lv.font_FjallaOne_Regular_22)
except AttributeError:
    try:
        style_setting_screen_low_labal_main_main_default.set_text_font(lv.font_montserrat_22)
    except AttributeError:
        style_setting_screen_low_labal_main_main_default.set_text_font(lv.font_montserrat_16)
style_setting_screen_low_labal_main_main_default.set_text_letter_space(0)
style_setting_screen_low_labal_main_main_default.set_pad_left(0)
style_setting_screen_low_labal_main_main_default.set_pad_right(0)
style_setting_screen_low_labal_main_main_default.set_pad_top(0)
style_setting_screen_low_labal_main_main_default.set_pad_bottom(0)

# add style for Setting_Screen_Low_Labal
Setting_Screen_Low_Labal.add_style(style_setting_screen_low_labal_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

Setting_Screen_Radio_Btn_Press = lv.img(Setting_Screen)
Setting_Screen_Radio_Btn_Press.set_pos(179,147)
Setting_Screen_Radio_Btn_Press.set_size(20,20)
Setting_Screen_Radio_Btn_Press.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp576789246.png','rb') as f:
        Setting_Screen_Radio_Btn_Press_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp576789246.png')
    sys.exit()

Setting_Screen_Radio_Btn_Press_img = lv.img_dsc_t({
  'data_size': len(Setting_Screen_Radio_Btn_Press_img_data),
  'header': {'always_zero': 0, 'w': 20, 'h': 20, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': Setting_Screen_Radio_Btn_Press_img_data
})

Setting_Screen_Radio_Btn_Press.set_src(Setting_Screen_Radio_Btn_Press_img)
Setting_Screen_Radio_Btn_Press.set_pivot(0,0)
Setting_Screen_Radio_Btn_Press.set_angle(0)
# create style style_setting_screen_radio_btn_press_main_main_default
style_setting_screen_radio_btn_press_main_main_default = lv.style_t()
style_setting_screen_radio_btn_press_main_main_default.init()
style_setting_screen_radio_btn_press_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_setting_screen_radio_btn_press_main_main_default.set_img_recolor_opa(0)
style_setting_screen_radio_btn_press_main_main_default.set_img_opa(0)

# add style for Setting_Screen_Radio_Btn_Press
Setting_Screen_Radio_Btn_Press.add_style(style_setting_screen_radio_btn_press_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

Setting_Screen_Radio_Btn_Released = lv.img(Setting_Screen)
Setting_Screen_Radio_Btn_Released.set_pos(180,97)
Setting_Screen_Radio_Btn_Released.set_size(20,20)
Setting_Screen_Radio_Btn_Released.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp1513430703.png','rb') as f:
        Setting_Screen_Radio_Btn_Released_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp1513430703.png')
    sys.exit()

Setting_Screen_Radio_Btn_Released_img = lv.img_dsc_t({
  'data_size': len(Setting_Screen_Radio_Btn_Released_img_data),
  'header': {'always_zero': 0, 'w': 20, 'h': 20, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': Setting_Screen_Radio_Btn_Released_img_data
})

Setting_Screen_Radio_Btn_Released.set_src(Setting_Screen_Radio_Btn_Released_img)
Setting_Screen_Radio_Btn_Released.set_pivot(0,0)
Setting_Screen_Radio_Btn_Released.set_angle(0)
# create style style_setting_screen_radio_btn_released_main_main_default
style_setting_screen_radio_btn_released_main_main_default = lv.style_t()
style_setting_screen_radio_btn_released_main_main_default.init()
style_setting_screen_radio_btn_released_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_setting_screen_radio_btn_released_main_main_default.set_img_recolor_opa(0)
style_setting_screen_radio_btn_released_main_main_default.set_img_opa(0)

# add style for Setting_Screen_Radio_Btn_Released
Setting_Screen_Radio_Btn_Released.add_style(style_setting_screen_radio_btn_released_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

Setting_Screen_Radio_Btn_Rel_3 = lv.img(Setting_Screen)
Setting_Screen_Radio_Btn_Rel_3.set_pos(178,200)
Setting_Screen_Radio_Btn_Rel_3.set_size(20,20)
Setting_Screen_Radio_Btn_Rel_3.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp1513430703.png','rb') as f:
        Setting_Screen_Radio_Btn_Rel_3_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp1513430703.png')
    sys.exit()

Setting_Screen_Radio_Btn_Rel_3_img = lv.img_dsc_t({
  'data_size': len(Setting_Screen_Radio_Btn_Rel_3_img_data),
  'header': {'always_zero': 0, 'w': 20, 'h': 20, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': Setting_Screen_Radio_Btn_Rel_3_img_data
})

Setting_Screen_Radio_Btn_Rel_3.set_src(Setting_Screen_Radio_Btn_Rel_3_img)
Setting_Screen_Radio_Btn_Rel_3.set_pivot(0,0)
Setting_Screen_Radio_Btn_Rel_3.set_angle(0)
# create style style_setting_screen_radio_btn_rel_3_main_main_default
style_setting_screen_radio_btn_rel_3_main_main_default = lv.style_t()
style_setting_screen_radio_btn_rel_3_main_main_default.init()
style_setting_screen_radio_btn_rel_3_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_setting_screen_radio_btn_rel_3_main_main_default.set_img_recolor_opa(0)
style_setting_screen_radio_btn_rel_3_main_main_default.set_img_opa(3)

# add style for Setting_Screen_Radio_Btn_Rel_3
Setting_Screen_Radio_Btn_Rel_3.add_style(style_setting_screen_radio_btn_rel_3_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

Setting_Screen_Brightness_Icon = lv.img(Setting_Screen)
Setting_Screen_Brightness_Icon.set_pos(14,143)
Setting_Screen_Brightness_Icon.set_size(30,30)
Setting_Screen_Brightness_Icon.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp497948062.png','rb') as f:
        Setting_Screen_Brightness_Icon_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp497948062.png')
    sys.exit()

Setting_Screen_Brightness_Icon_img = lv.img_dsc_t({
  'data_size': len(Setting_Screen_Brightness_Icon_img_data),
  'header': {'always_zero': 0, 'w': 30, 'h': 30, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': Setting_Screen_Brightness_Icon_img_data
})

Setting_Screen_Brightness_Icon.set_src(Setting_Screen_Brightness_Icon_img)
Setting_Screen_Brightness_Icon.set_pivot(0,0)
Setting_Screen_Brightness_Icon.set_angle(0)
# create style style_setting_screen_brightness_icon_main_main_default
style_setting_screen_brightness_icon_main_main_default = lv.style_t()
style_setting_screen_brightness_icon_main_main_default.init()
style_setting_screen_brightness_icon_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_setting_screen_brightness_icon_main_main_default.set_img_recolor_opa(0)
style_setting_screen_brightness_icon_main_main_default.set_img_opa(0)

# add style for Setting_Screen_Brightness_Icon
Setting_Screen_Brightness_Icon.add_style(style_setting_screen_brightness_icon_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

Setting_Screen_About_Icon = lv.img(Setting_Screen)
Setting_Screen_About_Icon.set_pos(14,143)
Setting_Screen_About_Icon.set_size(30,30)
Setting_Screen_About_Icon.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-308500653.png','rb') as f:
        Setting_Screen_About_Icon_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-308500653.png')
    sys.exit()

Setting_Screen_About_Icon_img = lv.img_dsc_t({
  'data_size': len(Setting_Screen_About_Icon_img_data),
  'header': {'always_zero': 0, 'w': 30, 'h': 30, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': Setting_Screen_About_Icon_img_data
})

Setting_Screen_About_Icon.set_src(Setting_Screen_About_Icon_img)
Setting_Screen_About_Icon.set_pivot(0,0)
Setting_Screen_About_Icon.set_angle(0)
# create style style_setting_screen_about_icon_main_main_default
style_setting_screen_about_icon_main_main_default = lv.style_t()
style_setting_screen_about_icon_main_main_default.init()
style_setting_screen_about_icon_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_setting_screen_about_icon_main_main_default.set_img_recolor_opa(0)
style_setting_screen_about_icon_main_main_default.set_img_opa(0)

# add style for Setting_Screen_About_Icon
Setting_Screen_About_Icon.add_style(style_setting_screen_about_icon_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

Setting_Screen_Menu_Icon = lv.img(Setting_Screen)
Setting_Screen_Menu_Icon.set_pos(14,143)
Setting_Screen_Menu_Icon.set_size(30,30)
Setting_Screen_Menu_Icon.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1071354425.png','rb') as f:
        Setting_Screen_Menu_Icon_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1071354425.png')
    sys.exit()

Setting_Screen_Menu_Icon_img = lv.img_dsc_t({
  'data_size': len(Setting_Screen_Menu_Icon_img_data),
  'header': {'always_zero': 0, 'w': 30, 'h': 30, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': Setting_Screen_Menu_Icon_img_data
})

Setting_Screen_Menu_Icon.set_src(Setting_Screen_Menu_Icon_img)
Setting_Screen_Menu_Icon.set_pivot(0,0)
Setting_Screen_Menu_Icon.set_angle(0)
# create style style_setting_screen_menu_icon_main_main_default
style_setting_screen_menu_icon_main_main_default = lv.style_t()
style_setting_screen_menu_icon_main_main_default.init()
style_setting_screen_menu_icon_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_setting_screen_menu_icon_main_main_default.set_img_recolor_opa(0)
style_setting_screen_menu_icon_main_main_default.set_img_opa(0)

# add style for Setting_Screen_Menu_Icon
Setting_Screen_Menu_Icon.add_style(style_setting_screen_menu_icon_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

Setting_Screen_Date_Text = lv.label(Setting_Screen)
Setting_Screen_Date_Text.set_pos(56,148)
Setting_Screen_Date_Text.set_size(21,15)
Setting_Screen_Date_Text.set_text("15")
Setting_Screen_Date_Text.set_long_mode(lv.label.LONG.WRAP)
Setting_Screen_Date_Text.set_style_text_align(lv.TEXT_ALIGN.RIGHT, 0)
# create style style_setting_screen_date_text_main_main_default
style_setting_screen_date_text_main_main_default = lv.style_t()
style_setting_screen_date_text_main_main_default.init()
style_setting_screen_date_text_main_main_default.set_radius(0)
style_setting_screen_date_text_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_setting_screen_date_text_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_setting_screen_date_text_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_setting_screen_date_text_main_main_default.set_bg_opa(0)
style_setting_screen_date_text_main_main_default.set_text_color(lv.color_make(0xf9,0xf6,0xf6))
try:
    style_setting_screen_date_text_main_main_default.set_text_font(lv.font_FjallaOne_Regular_16)
except AttributeError:
    try:
        style_setting_screen_date_text_main_main_default.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_setting_screen_date_text_main_main_default.set_text_font(lv.font_montserrat_16)
style_setting_screen_date_text_main_main_default.set_text_letter_space(2)
style_setting_screen_date_text_main_main_default.set_pad_left(0)
style_setting_screen_date_text_main_main_default.set_pad_right(0)
style_setting_screen_date_text_main_main_default.set_pad_top(0)
style_setting_screen_date_text_main_main_default.set_pad_bottom(0)

# add style for Setting_Screen_Date_Text
Setting_Screen_Date_Text.add_style(style_setting_screen_date_text_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

Setting_Screen_Month_Text = lv.label(Setting_Screen)
Setting_Screen_Month_Text.set_pos(98,148)
Setting_Screen_Month_Text.set_size(21,15)
Setting_Screen_Month_Text.set_text("03")
Setting_Screen_Month_Text.set_long_mode(lv.label.LONG.WRAP)
Setting_Screen_Month_Text.set_style_text_align(lv.TEXT_ALIGN.CENTER, 0)
# create style style_setting_screen_month_text_main_main_default
style_setting_screen_month_text_main_main_default = lv.style_t()
style_setting_screen_month_text_main_main_default.init()
style_setting_screen_month_text_main_main_default.set_radius(0)
style_setting_screen_month_text_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_setting_screen_month_text_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_setting_screen_month_text_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_setting_screen_month_text_main_main_default.set_bg_opa(0)
style_setting_screen_month_text_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_setting_screen_month_text_main_main_default.set_text_font(lv.font_FjallaOne_Regular_16)
except AttributeError:
    try:
        style_setting_screen_month_text_main_main_default.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_setting_screen_month_text_main_main_default.set_text_font(lv.font_montserrat_16)
style_setting_screen_month_text_main_main_default.set_text_letter_space(2)
style_setting_screen_month_text_main_main_default.set_pad_left(0)
style_setting_screen_month_text_main_main_default.set_pad_right(0)
style_setting_screen_month_text_main_main_default.set_pad_top(0)
style_setting_screen_month_text_main_main_default.set_pad_bottom(0)

# add style for Setting_Screen_Month_Text
Setting_Screen_Month_Text.add_style(style_setting_screen_month_text_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

Setting_Screen_Year_Text = lv.label(Setting_Screen)
Setting_Screen_Year_Text.set_pos(136,148)
Setting_Screen_Year_Text.set_size(42,15)
Setting_Screen_Year_Text.set_text("2022")
Setting_Screen_Year_Text.set_long_mode(lv.label.LONG.WRAP)
Setting_Screen_Year_Text.set_style_text_align(lv.TEXT_ALIGN.CENTER, 0)
# create style style_setting_screen_year_text_main_main_default
style_setting_screen_year_text_main_main_default = lv.style_t()
style_setting_screen_year_text_main_main_default.init()
style_setting_screen_year_text_main_main_default.set_radius(0)
style_setting_screen_year_text_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_setting_screen_year_text_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_setting_screen_year_text_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_setting_screen_year_text_main_main_default.set_bg_opa(0)
style_setting_screen_year_text_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_setting_screen_year_text_main_main_default.set_text_font(lv.font_FjallaOne_Regular_16)
except AttributeError:
    try:
        style_setting_screen_year_text_main_main_default.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_setting_screen_year_text_main_main_default.set_text_font(lv.font_montserrat_16)
style_setting_screen_year_text_main_main_default.set_text_letter_space(2)
style_setting_screen_year_text_main_main_default.set_pad_left(0)
style_setting_screen_year_text_main_main_default.set_pad_right(0)
style_setting_screen_year_text_main_main_default.set_pad_top(0)
style_setting_screen_year_text_main_main_default.set_pad_bottom(0)

# add style for Setting_Screen_Year_Text
Setting_Screen_Year_Text.add_style(style_setting_screen_year_text_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

Setting_Screen_Date_Up_Org = lv.img(Setting_Screen)
Setting_Screen_Date_Up_Org.set_pos(58,128)
Setting_Screen_Date_Up_Org.set_size(21,25)
Setting_Screen_Date_Up_Org.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp638267427.png','rb') as f:
        Setting_Screen_Date_Up_Org_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp638267427.png')
    sys.exit()

Setting_Screen_Date_Up_Org_img = lv.img_dsc_t({
  'data_size': len(Setting_Screen_Date_Up_Org_img_data),
  'header': {'always_zero': 0, 'w': 21, 'h': 25, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': Setting_Screen_Date_Up_Org_img_data
})

Setting_Screen_Date_Up_Org.set_src(Setting_Screen_Date_Up_Org_img)
Setting_Screen_Date_Up_Org.set_pivot(0,0)
Setting_Screen_Date_Up_Org.set_angle(0)
# create style style_setting_screen_date_up_org_main_main_default
style_setting_screen_date_up_org_main_main_default = lv.style_t()
style_setting_screen_date_up_org_main_main_default.init()
style_setting_screen_date_up_org_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_setting_screen_date_up_org_main_main_default.set_img_recolor_opa(0)
style_setting_screen_date_up_org_main_main_default.set_img_opa(0)

# add style for Setting_Screen_Date_Up_Org
Setting_Screen_Date_Up_Org.add_style(style_setting_screen_date_up_org_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

Setting_Screen_Date_Up_Whi = lv.img(Setting_Screen)
Setting_Screen_Date_Up_Whi.set_pos(58,128)
Setting_Screen_Date_Up_Whi.set_size(17,19)
Setting_Screen_Date_Up_Whi.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp93421828.png','rb') as f:
        Setting_Screen_Date_Up_Whi_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp93421828.png')
    sys.exit()

Setting_Screen_Date_Up_Whi_img = lv.img_dsc_t({
  'data_size': len(Setting_Screen_Date_Up_Whi_img_data),
  'header': {'always_zero': 0, 'w': 17, 'h': 19, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': Setting_Screen_Date_Up_Whi_img_data
})

Setting_Screen_Date_Up_Whi.set_src(Setting_Screen_Date_Up_Whi_img)
Setting_Screen_Date_Up_Whi.set_pivot(0,0)
Setting_Screen_Date_Up_Whi.set_angle(0)
# create style style_setting_screen_date_up_whi_main_main_default
style_setting_screen_date_up_whi_main_main_default = lv.style_t()
style_setting_screen_date_up_whi_main_main_default.init()
style_setting_screen_date_up_whi_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_setting_screen_date_up_whi_main_main_default.set_img_recolor_opa(0)
style_setting_screen_date_up_whi_main_main_default.set_img_opa(255)

# add style for Setting_Screen_Date_Up_Whi
Setting_Screen_Date_Up_Whi.add_style(style_setting_screen_date_up_whi_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

Setting_Screen_Date_Down_Org = lv.img(Setting_Screen)
Setting_Screen_Date_Down_Org.set_pos(58,177)
Setting_Screen_Date_Down_Org.set_size(21,25)
Setting_Screen_Date_Down_Org.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp851363158.png','rb') as f:
        Setting_Screen_Date_Down_Org_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp851363158.png')
    sys.exit()

Setting_Screen_Date_Down_Org_img = lv.img_dsc_t({
  'data_size': len(Setting_Screen_Date_Down_Org_img_data),
  'header': {'always_zero': 0, 'w': 21, 'h': 25, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': Setting_Screen_Date_Down_Org_img_data
})

Setting_Screen_Date_Down_Org.set_src(Setting_Screen_Date_Down_Org_img)
Setting_Screen_Date_Down_Org.set_pivot(0,0)
Setting_Screen_Date_Down_Org.set_angle(0)
# create style style_setting_screen_date_down_org_main_main_default
style_setting_screen_date_down_org_main_main_default = lv.style_t()
style_setting_screen_date_down_org_main_main_default.init()
style_setting_screen_date_down_org_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_setting_screen_date_down_org_main_main_default.set_img_recolor_opa(0)
style_setting_screen_date_down_org_main_main_default.set_img_opa(0)

# add style for Setting_Screen_Date_Down_Org
Setting_Screen_Date_Down_Org.add_style(style_setting_screen_date_down_org_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

Setting_Screen_Date_Down_Whi = lv.img(Setting_Screen)
Setting_Screen_Date_Down_Whi.set_pos(58,177)
Setting_Screen_Date_Down_Whi.set_size(21,25)
Setting_Screen_Date_Down_Whi.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp1076359549.png','rb') as f:
        Setting_Screen_Date_Down_Whi_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp1076359549.png')
    sys.exit()

Setting_Screen_Date_Down_Whi_img = lv.img_dsc_t({
  'data_size': len(Setting_Screen_Date_Down_Whi_img_data),
  'header': {'always_zero': 0, 'w': 21, 'h': 25, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': Setting_Screen_Date_Down_Whi_img_data
})

Setting_Screen_Date_Down_Whi.set_src(Setting_Screen_Date_Down_Whi_img)
Setting_Screen_Date_Down_Whi.set_pivot(0,0)
Setting_Screen_Date_Down_Whi.set_angle(0)
# create style style_setting_screen_date_down_whi_main_main_default
style_setting_screen_date_down_whi_main_main_default = lv.style_t()
style_setting_screen_date_down_whi_main_main_default.init()
style_setting_screen_date_down_whi_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_setting_screen_date_down_whi_main_main_default.set_img_recolor_opa(0)
style_setting_screen_date_down_whi_main_main_default.set_img_opa(255)

# add style for Setting_Screen_Date_Down_Whi
Setting_Screen_Date_Down_Whi.add_style(style_setting_screen_date_down_whi_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

Setting_Screen_Month_Up_Org = lv.img(Setting_Screen)
Setting_Screen_Month_Up_Org.set_pos(97,123)
Setting_Screen_Month_Up_Org.set_size(21,25)
Setting_Screen_Month_Up_Org.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp638267427.png','rb') as f:
        Setting_Screen_Month_Up_Org_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp638267427.png')
    sys.exit()

Setting_Screen_Month_Up_Org_img = lv.img_dsc_t({
  'data_size': len(Setting_Screen_Month_Up_Org_img_data),
  'header': {'always_zero': 0, 'w': 21, 'h': 25, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': Setting_Screen_Month_Up_Org_img_data
})

Setting_Screen_Month_Up_Org.set_src(Setting_Screen_Month_Up_Org_img)
Setting_Screen_Month_Up_Org.set_pivot(0,0)
Setting_Screen_Month_Up_Org.set_angle(0)
# create style style_setting_screen_month_up_org_main_main_default
style_setting_screen_month_up_org_main_main_default = lv.style_t()
style_setting_screen_month_up_org_main_main_default.init()
style_setting_screen_month_up_org_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_setting_screen_month_up_org_main_main_default.set_img_recolor_opa(0)
style_setting_screen_month_up_org_main_main_default.set_img_opa(0)

# add style for Setting_Screen_Month_Up_Org
Setting_Screen_Month_Up_Org.add_style(style_setting_screen_month_up_org_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

Setting_Screen_Month_Up_Whi = lv.img(Setting_Screen)
Setting_Screen_Month_Up_Whi.set_pos(100,126)
Setting_Screen_Month_Up_Whi.set_size(17,19)
Setting_Screen_Month_Up_Whi.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp93421828.png','rb') as f:
        Setting_Screen_Month_Up_Whi_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp93421828.png')
    sys.exit()

Setting_Screen_Month_Up_Whi_img = lv.img_dsc_t({
  'data_size': len(Setting_Screen_Month_Up_Whi_img_data),
  'header': {'always_zero': 0, 'w': 17, 'h': 19, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': Setting_Screen_Month_Up_Whi_img_data
})

Setting_Screen_Month_Up_Whi.set_src(Setting_Screen_Month_Up_Whi_img)
Setting_Screen_Month_Up_Whi.set_pivot(0,0)
Setting_Screen_Month_Up_Whi.set_angle(0)
# create style style_setting_screen_month_up_whi_main_main_default
style_setting_screen_month_up_whi_main_main_default = lv.style_t()
style_setting_screen_month_up_whi_main_main_default.init()
style_setting_screen_month_up_whi_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_setting_screen_month_up_whi_main_main_default.set_img_recolor_opa(0)
style_setting_screen_month_up_whi_main_main_default.set_img_opa(253)

# add style for Setting_Screen_Month_Up_Whi
Setting_Screen_Month_Up_Whi.add_style(style_setting_screen_month_up_whi_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

Setting_Screen_Month_Down_Org = lv.img(Setting_Screen)
Setting_Screen_Month_Down_Org.set_pos(101,177)
Setting_Screen_Month_Down_Org.set_size(21,25)
Setting_Screen_Month_Down_Org.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp851363158.png','rb') as f:
        Setting_Screen_Month_Down_Org_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp851363158.png')
    sys.exit()

Setting_Screen_Month_Down_Org_img = lv.img_dsc_t({
  'data_size': len(Setting_Screen_Month_Down_Org_img_data),
  'header': {'always_zero': 0, 'w': 21, 'h': 25, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': Setting_Screen_Month_Down_Org_img_data
})

Setting_Screen_Month_Down_Org.set_src(Setting_Screen_Month_Down_Org_img)
Setting_Screen_Month_Down_Org.set_pivot(0,0)
Setting_Screen_Month_Down_Org.set_angle(0)
# create style style_setting_screen_month_down_org_main_main_default
style_setting_screen_month_down_org_main_main_default = lv.style_t()
style_setting_screen_month_down_org_main_main_default.init()
style_setting_screen_month_down_org_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_setting_screen_month_down_org_main_main_default.set_img_recolor_opa(0)
style_setting_screen_month_down_org_main_main_default.set_img_opa(0)

# add style for Setting_Screen_Month_Down_Org
Setting_Screen_Month_Down_Org.add_style(style_setting_screen_month_down_org_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

Setting_Screen_Month_Down_Whi = lv.img(Setting_Screen)
Setting_Screen_Month_Down_Whi.set_pos(100,177)
Setting_Screen_Month_Down_Whi.set_size(20,24)
Setting_Screen_Month_Down_Whi.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp567521723.png','rb') as f:
        Setting_Screen_Month_Down_Whi_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp567521723.png')
    sys.exit()

Setting_Screen_Month_Down_Whi_img = lv.img_dsc_t({
  'data_size': len(Setting_Screen_Month_Down_Whi_img_data),
  'header': {'always_zero': 0, 'w': 20, 'h': 24, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': Setting_Screen_Month_Down_Whi_img_data
})

Setting_Screen_Month_Down_Whi.set_src(Setting_Screen_Month_Down_Whi_img)
Setting_Screen_Month_Down_Whi.set_pivot(0,0)
Setting_Screen_Month_Down_Whi.set_angle(0)
# create style style_setting_screen_month_down_whi_main_main_default
style_setting_screen_month_down_whi_main_main_default = lv.style_t()
style_setting_screen_month_down_whi_main_main_default.init()
style_setting_screen_month_down_whi_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_setting_screen_month_down_whi_main_main_default.set_img_recolor_opa(0)
style_setting_screen_month_down_whi_main_main_default.set_img_opa(255)

# add style for Setting_Screen_Month_Down_Whi
Setting_Screen_Month_Down_Whi.add_style(style_setting_screen_month_down_whi_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

Setting_Screen_Year_Up_Org = lv.img(Setting_Screen)
Setting_Screen_Year_Up_Org.set_pos(143,121)
Setting_Screen_Year_Up_Org.set_size(21,25)
Setting_Screen_Year_Up_Org.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp638267427.png','rb') as f:
        Setting_Screen_Year_Up_Org_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp638267427.png')
    sys.exit()

Setting_Screen_Year_Up_Org_img = lv.img_dsc_t({
  'data_size': len(Setting_Screen_Year_Up_Org_img_data),
  'header': {'always_zero': 0, 'w': 21, 'h': 25, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': Setting_Screen_Year_Up_Org_img_data
})

Setting_Screen_Year_Up_Org.set_src(Setting_Screen_Year_Up_Org_img)
Setting_Screen_Year_Up_Org.set_pivot(0,0)
Setting_Screen_Year_Up_Org.set_angle(0)
# create style style_setting_screen_year_up_org_main_main_default
style_setting_screen_year_up_org_main_main_default = lv.style_t()
style_setting_screen_year_up_org_main_main_default.init()
style_setting_screen_year_up_org_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_setting_screen_year_up_org_main_main_default.set_img_recolor_opa(0)
style_setting_screen_year_up_org_main_main_default.set_img_opa(0)

# add style for Setting_Screen_Year_Up_Org
Setting_Screen_Year_Up_Org.add_style(style_setting_screen_year_up_org_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

Setting_Screen_Year_Up_Whi = lv.img(Setting_Screen)
Setting_Screen_Year_Up_Whi.set_pos(143,126)
Setting_Screen_Year_Up_Whi.set_size(19,21)
Setting_Screen_Year_Up_Whi.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-534169955.png','rb') as f:
        Setting_Screen_Year_Up_Whi_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-534169955.png')
    sys.exit()

Setting_Screen_Year_Up_Whi_img = lv.img_dsc_t({
  'data_size': len(Setting_Screen_Year_Up_Whi_img_data),
  'header': {'always_zero': 0, 'w': 19, 'h': 21, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': Setting_Screen_Year_Up_Whi_img_data
})

Setting_Screen_Year_Up_Whi.set_src(Setting_Screen_Year_Up_Whi_img)
Setting_Screen_Year_Up_Whi.set_pivot(0,0)
Setting_Screen_Year_Up_Whi.set_angle(0)
# create style style_setting_screen_year_up_whi_main_main_default
style_setting_screen_year_up_whi_main_main_default = lv.style_t()
style_setting_screen_year_up_whi_main_main_default.init()
style_setting_screen_year_up_whi_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_setting_screen_year_up_whi_main_main_default.set_img_recolor_opa(0)
style_setting_screen_year_up_whi_main_main_default.set_img_opa(255)

# add style for Setting_Screen_Year_Up_Whi
Setting_Screen_Year_Up_Whi.add_style(style_setting_screen_year_up_whi_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

Setting_Screen_Year_Down_Org = lv.img(Setting_Screen)
Setting_Screen_Year_Down_Org.set_pos(145,176)
Setting_Screen_Year_Down_Org.set_size(21,25)
Setting_Screen_Year_Down_Org.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp851363158.png','rb') as f:
        Setting_Screen_Year_Down_Org_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp851363158.png')
    sys.exit()

Setting_Screen_Year_Down_Org_img = lv.img_dsc_t({
  'data_size': len(Setting_Screen_Year_Down_Org_img_data),
  'header': {'always_zero': 0, 'w': 21, 'h': 25, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': Setting_Screen_Year_Down_Org_img_data
})

Setting_Screen_Year_Down_Org.set_src(Setting_Screen_Year_Down_Org_img)
Setting_Screen_Year_Down_Org.set_pivot(0,0)
Setting_Screen_Year_Down_Org.set_angle(0)
# create style style_setting_screen_year_down_org_main_main_default
style_setting_screen_year_down_org_main_main_default = lv.style_t()
style_setting_screen_year_down_org_main_main_default.init()
style_setting_screen_year_down_org_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_setting_screen_year_down_org_main_main_default.set_img_recolor_opa(0)
style_setting_screen_year_down_org_main_main_default.set_img_opa(0)

# add style for Setting_Screen_Year_Down_Org
Setting_Screen_Year_Down_Org.add_style(style_setting_screen_year_down_org_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

Setting_Screen_Year_Down_Whi = lv.img(Setting_Screen)
Setting_Screen_Year_Down_Whi.set_pos(143,177)
Setting_Screen_Year_Down_Whi.set_size(21,24)
Setting_Screen_Year_Down_Whi.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-276950148.png','rb') as f:
        Setting_Screen_Year_Down_Whi_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-276950148.png')
    sys.exit()

Setting_Screen_Year_Down_Whi_img = lv.img_dsc_t({
  'data_size': len(Setting_Screen_Year_Down_Whi_img_data),
  'header': {'always_zero': 0, 'w': 21, 'h': 24, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': Setting_Screen_Year_Down_Whi_img_data
})

Setting_Screen_Year_Down_Whi.set_src(Setting_Screen_Year_Down_Whi_img)
Setting_Screen_Year_Down_Whi.set_pivot(0,0)
Setting_Screen_Year_Down_Whi.set_angle(0)
# create style style_setting_screen_year_down_whi_main_main_default
style_setting_screen_year_down_whi_main_main_default = lv.style_t()
style_setting_screen_year_down_whi_main_main_default.init()
style_setting_screen_year_down_whi_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_setting_screen_year_down_whi_main_main_default.set_img_recolor_opa(0)
style_setting_screen_year_down_whi_main_main_default.set_img_opa(255)

# add style for Setting_Screen_Year_Down_Whi
Setting_Screen_Year_Down_Whi.add_style(style_setting_screen_year_down_whi_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

Setting_Screen_Hour_Text = lv.label(Setting_Screen)
Setting_Screen_Hour_Text.set_pos(56,148)
Setting_Screen_Hour_Text.set_size(21,15)
Setting_Screen_Hour_Text.set_text("20")
Setting_Screen_Hour_Text.set_long_mode(lv.label.LONG.WRAP)
Setting_Screen_Hour_Text.set_style_text_align(lv.TEXT_ALIGN.CENTER, 0)
# create style style_setting_screen_hour_text_main_main_default
style_setting_screen_hour_text_main_main_default = lv.style_t()
style_setting_screen_hour_text_main_main_default.init()
style_setting_screen_hour_text_main_main_default.set_radius(0)
style_setting_screen_hour_text_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_setting_screen_hour_text_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_setting_screen_hour_text_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_setting_screen_hour_text_main_main_default.set_bg_opa(0)
style_setting_screen_hour_text_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_setting_screen_hour_text_main_main_default.set_text_font(lv.font_FjallaOne_Regular_16)
except AttributeError:
    try:
        style_setting_screen_hour_text_main_main_default.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_setting_screen_hour_text_main_main_default.set_text_font(lv.font_montserrat_16)
style_setting_screen_hour_text_main_main_default.set_text_letter_space(2)
style_setting_screen_hour_text_main_main_default.set_pad_left(0)
style_setting_screen_hour_text_main_main_default.set_pad_right(0)
style_setting_screen_hour_text_main_main_default.set_pad_top(0)
style_setting_screen_hour_text_main_main_default.set_pad_bottom(0)

# add style for Setting_Screen_Hour_Text
Setting_Screen_Hour_Text.add_style(style_setting_screen_hour_text_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

Setting_Screen_Min_Text = lv.label(Setting_Screen)
Setting_Screen_Min_Text.set_pos(98,148)
Setting_Screen_Min_Text.set_size(21,15)
Setting_Screen_Min_Text.set_text("03")
Setting_Screen_Min_Text.set_long_mode(lv.label.LONG.WRAP)
Setting_Screen_Min_Text.set_style_text_align(lv.TEXT_ALIGN.CENTER, 0)
# create style style_setting_screen_min_text_main_main_default
style_setting_screen_min_text_main_main_default = lv.style_t()
style_setting_screen_min_text_main_main_default.init()
style_setting_screen_min_text_main_main_default.set_radius(0)
style_setting_screen_min_text_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_setting_screen_min_text_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_setting_screen_min_text_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_setting_screen_min_text_main_main_default.set_bg_opa(0)
style_setting_screen_min_text_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_setting_screen_min_text_main_main_default.set_text_font(lv.font_FjallaOne_Regular_16)
except AttributeError:
    try:
        style_setting_screen_min_text_main_main_default.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_setting_screen_min_text_main_main_default.set_text_font(lv.font_montserrat_16)
style_setting_screen_min_text_main_main_default.set_text_letter_space(2)
style_setting_screen_min_text_main_main_default.set_pad_left(0)
style_setting_screen_min_text_main_main_default.set_pad_right(0)
style_setting_screen_min_text_main_main_default.set_pad_top(0)
style_setting_screen_min_text_main_main_default.set_pad_bottom(0)

# add style for Setting_Screen_Min_Text
Setting_Screen_Min_Text.add_style(style_setting_screen_min_text_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

Setting_Screen_Hour_Up_Whi = lv.img(Setting_Screen)
Setting_Screen_Hour_Up_Whi.set_pos(75,128)
Setting_Screen_Hour_Up_Whi.set_size(17,19)
Setting_Screen_Hour_Up_Whi.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp93421828.png','rb') as f:
        Setting_Screen_Hour_Up_Whi_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp93421828.png')
    sys.exit()

Setting_Screen_Hour_Up_Whi_img = lv.img_dsc_t({
  'data_size': len(Setting_Screen_Hour_Up_Whi_img_data),
  'header': {'always_zero': 0, 'w': 17, 'h': 19, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': Setting_Screen_Hour_Up_Whi_img_data
})

Setting_Screen_Hour_Up_Whi.set_src(Setting_Screen_Hour_Up_Whi_img)
Setting_Screen_Hour_Up_Whi.set_pivot(0,0)
Setting_Screen_Hour_Up_Whi.set_angle(0)
# create style style_setting_screen_hour_up_whi_main_main_default
style_setting_screen_hour_up_whi_main_main_default = lv.style_t()
style_setting_screen_hour_up_whi_main_main_default.init()
style_setting_screen_hour_up_whi_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_setting_screen_hour_up_whi_main_main_default.set_img_recolor_opa(0)
style_setting_screen_hour_up_whi_main_main_default.set_img_opa(0)

# add style for Setting_Screen_Hour_Up_Whi
Setting_Screen_Hour_Up_Whi.add_style(style_setting_screen_hour_up_whi_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

Setting_Screen_Hour_Down_Whi = lv.img(Setting_Screen)
Setting_Screen_Hour_Down_Whi.set_pos(75,177)
Setting_Screen_Hour_Down_Whi.set_size(21,24)
Setting_Screen_Hour_Down_Whi.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-276950148.png','rb') as f:
        Setting_Screen_Hour_Down_Whi_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-276950148.png')
    sys.exit()

Setting_Screen_Hour_Down_Whi_img = lv.img_dsc_t({
  'data_size': len(Setting_Screen_Hour_Down_Whi_img_data),
  'header': {'always_zero': 0, 'w': 21, 'h': 24, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': Setting_Screen_Hour_Down_Whi_img_data
})

Setting_Screen_Hour_Down_Whi.set_src(Setting_Screen_Hour_Down_Whi_img)
Setting_Screen_Hour_Down_Whi.set_pivot(0,0)
Setting_Screen_Hour_Down_Whi.set_angle(0)
# create style style_setting_screen_hour_down_whi_main_main_default
style_setting_screen_hour_down_whi_main_main_default = lv.style_t()
style_setting_screen_hour_down_whi_main_main_default.init()
style_setting_screen_hour_down_whi_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_setting_screen_hour_down_whi_main_main_default.set_img_recolor_opa(0)
style_setting_screen_hour_down_whi_main_main_default.set_img_opa(0)

# add style for Setting_Screen_Hour_Down_Whi
Setting_Screen_Hour_Down_Whi.add_style(style_setting_screen_hour_down_whi_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

Setting_Screen_Min_Up_Whi = lv.img(Setting_Screen)
Setting_Screen_Min_Up_Whi.set_pos(118,128)
Setting_Screen_Min_Up_Whi.set_size(17,19)
Setting_Screen_Min_Up_Whi.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp93421828.png','rb') as f:
        Setting_Screen_Min_Up_Whi_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp93421828.png')
    sys.exit()

Setting_Screen_Min_Up_Whi_img = lv.img_dsc_t({
  'data_size': len(Setting_Screen_Min_Up_Whi_img_data),
  'header': {'always_zero': 0, 'w': 17, 'h': 19, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': Setting_Screen_Min_Up_Whi_img_data
})

Setting_Screen_Min_Up_Whi.set_src(Setting_Screen_Min_Up_Whi_img)
Setting_Screen_Min_Up_Whi.set_pivot(0,0)
Setting_Screen_Min_Up_Whi.set_angle(0)
# create style style_setting_screen_min_up_whi_main_main_default
style_setting_screen_min_up_whi_main_main_default = lv.style_t()
style_setting_screen_min_up_whi_main_main_default.init()
style_setting_screen_min_up_whi_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_setting_screen_min_up_whi_main_main_default.set_img_recolor_opa(0)
style_setting_screen_min_up_whi_main_main_default.set_img_opa(0)

# add style for Setting_Screen_Min_Up_Whi
Setting_Screen_Min_Up_Whi.add_style(style_setting_screen_min_up_whi_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

Setting_Screen_Min_Down_Whi = lv.img(Setting_Screen)
Setting_Screen_Min_Down_Whi.set_pos(117,177)
Setting_Screen_Min_Down_Whi.set_size(21,24)
Setting_Screen_Min_Down_Whi.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-276950148.png','rb') as f:
        Setting_Screen_Min_Down_Whi_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-276950148.png')
    sys.exit()

Setting_Screen_Min_Down_Whi_img = lv.img_dsc_t({
  'data_size': len(Setting_Screen_Min_Down_Whi_img_data),
  'header': {'always_zero': 0, 'w': 21, 'h': 24, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': Setting_Screen_Min_Down_Whi_img_data
})

Setting_Screen_Min_Down_Whi.set_src(Setting_Screen_Min_Down_Whi_img)
Setting_Screen_Min_Down_Whi.set_pivot(0,0)
Setting_Screen_Min_Down_Whi.set_angle(0)
# create style style_setting_screen_min_down_whi_main_main_default
style_setting_screen_min_down_whi_main_main_default = lv.style_t()
style_setting_screen_min_down_whi_main_main_default.init()
style_setting_screen_min_down_whi_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_setting_screen_min_down_whi_main_main_default.set_img_recolor_opa(0)
style_setting_screen_min_down_whi_main_main_default.set_img_opa(0)

# add style for Setting_Screen_Min_Down_Whi
Setting_Screen_Min_Down_Whi.add_style(style_setting_screen_min_down_whi_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

Setting_Screen_AM_PM_Text = lv.label(Setting_Screen)
Setting_Screen_AM_PM_Text.set_pos(131,148)
Setting_Screen_AM_PM_Text.set_size(42,32)
Setting_Screen_AM_PM_Text.set_text("AM")
Setting_Screen_AM_PM_Text.set_long_mode(lv.label.LONG.WRAP)
Setting_Screen_AM_PM_Text.set_style_text_align(lv.TEXT_ALIGN.CENTER, 0)
# create style style_setting_screen_am_pm_text_main_main_default
style_setting_screen_am_pm_text_main_main_default = lv.style_t()
style_setting_screen_am_pm_text_main_main_default.init()
style_setting_screen_am_pm_text_main_main_default.set_radius(0)
style_setting_screen_am_pm_text_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_setting_screen_am_pm_text_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_setting_screen_am_pm_text_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_setting_screen_am_pm_text_main_main_default.set_bg_opa(0)
style_setting_screen_am_pm_text_main_main_default.set_text_color(lv.color_make(0xf5,0xf5,0xf5))
try:
    style_setting_screen_am_pm_text_main_main_default.set_text_font(lv.font_FjallaOne_Regular_16)
except AttributeError:
    try:
        style_setting_screen_am_pm_text_main_main_default.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_setting_screen_am_pm_text_main_main_default.set_text_font(lv.font_montserrat_16)
style_setting_screen_am_pm_text_main_main_default.set_text_letter_space(2)
style_setting_screen_am_pm_text_main_main_default.set_pad_left(0)
style_setting_screen_am_pm_text_main_main_default.set_pad_right(0)
style_setting_screen_am_pm_text_main_main_default.set_pad_top(0)
style_setting_screen_am_pm_text_main_main_default.set_pad_bottom(0)

# add style for Setting_Screen_AM_PM_Text
Setting_Screen_AM_PM_Text.add_style(style_setting_screen_am_pm_text_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

Setting_Screen_Clock_AM = lv.label(Setting_Screen)
Setting_Screen_Clock_AM.set_pos(128,285)
Setting_Screen_Clock_AM.set_size(28,13)
Setting_Screen_Clock_AM.set_text("AM")
Setting_Screen_Clock_AM.set_long_mode(lv.label.LONG.WRAP)
Setting_Screen_Clock_AM.set_style_text_align(lv.TEXT_ALIGN.CENTER, 0)
# create style style_setting_screen_clock_am_main_main_default
style_setting_screen_clock_am_main_main_default = lv.style_t()
style_setting_screen_clock_am_main_main_default.init()
style_setting_screen_clock_am_main_main_default.set_radius(0)
style_setting_screen_clock_am_main_main_default.set_bg_color(lv.color_make(0x00,0x00,0x00))
style_setting_screen_clock_am_main_main_default.set_bg_grad_color(lv.color_make(0x00,0x00,0x00))
style_setting_screen_clock_am_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_setting_screen_clock_am_main_main_default.set_bg_opa(0)
style_setting_screen_clock_am_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_setting_screen_clock_am_main_main_default.set_text_font(lv.font_FjallaOne_Regular_14)
except AttributeError:
    try:
        style_setting_screen_clock_am_main_main_default.set_text_font(lv.font_montserrat_14)
    except AttributeError:
        style_setting_screen_clock_am_main_main_default.set_text_font(lv.font_montserrat_16)
style_setting_screen_clock_am_main_main_default.set_text_letter_space(0)
style_setting_screen_clock_am_main_main_default.set_pad_left(0)
style_setting_screen_clock_am_main_main_default.set_pad_right(0)
style_setting_screen_clock_am_main_main_default.set_pad_top(0)
style_setting_screen_clock_am_main_main_default.set_pad_bottom(0)

# add style for Setting_Screen_Clock_AM
Setting_Screen_Clock_AM.add_style(style_setting_screen_clock_am_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

Setting_Screen_Hold_text = lv.label(Setting_Screen)
Setting_Screen_Hold_text.set_pos(42,227)
Setting_Screen_Hold_text.set_size(58,17)
Setting_Screen_Hold_text.set_text("Hold")
Setting_Screen_Hold_text.set_long_mode(lv.label.LONG.WRAP)
Setting_Screen_Hold_text.set_style_text_align(lv.TEXT_ALIGN.CENTER, 0)
# create style style_setting_screen_hold_text_main_main_default
style_setting_screen_hold_text_main_main_default = lv.style_t()
style_setting_screen_hold_text_main_main_default.init()
style_setting_screen_hold_text_main_main_default.set_radius(0)
style_setting_screen_hold_text_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_setting_screen_hold_text_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_setting_screen_hold_text_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_setting_screen_hold_text_main_main_default.set_bg_opa(0)
style_setting_screen_hold_text_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_setting_screen_hold_text_main_main_default.set_text_font(lv.font_FjallaOne_Regular_16)
except AttributeError:
    try:
        style_setting_screen_hold_text_main_main_default.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_setting_screen_hold_text_main_main_default.set_text_font(lv.font_montserrat_16)
style_setting_screen_hold_text_main_main_default.set_text_letter_space(0)
style_setting_screen_hold_text_main_main_default.set_pad_left(0)
style_setting_screen_hold_text_main_main_default.set_pad_right(0)
style_setting_screen_hold_text_main_main_default.set_pad_top(0)
style_setting_screen_hold_text_main_main_default.set_pad_bottom(0)

# add style for Setting_Screen_Hold_text
Setting_Screen_Hold_text.add_style(style_setting_screen_hold_text_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

Setting_Screen_Clock_Sub_Button = lv.img(Setting_Screen)
Setting_Screen_Clock_Sub_Button.set_pos(95,223)
Setting_Screen_Clock_Sub_Button.set_size(20,20)
Setting_Screen_Clock_Sub_Button.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp735427214.png','rb') as f:
        Setting_Screen_Clock_Sub_Button_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp735427214.png')
    sys.exit()

Setting_Screen_Clock_Sub_Button_img = lv.img_dsc_t({
  'data_size': len(Setting_Screen_Clock_Sub_Button_img_data),
  'header': {'always_zero': 0, 'w': 20, 'h': 20, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': Setting_Screen_Clock_Sub_Button_img_data
})

Setting_Screen_Clock_Sub_Button.set_src(Setting_Screen_Clock_Sub_Button_img)
Setting_Screen_Clock_Sub_Button.set_pivot(0,0)
Setting_Screen_Clock_Sub_Button.set_angle(0)
# create style style_setting_screen_clock_sub_button_main_main_default
style_setting_screen_clock_sub_button_main_main_default = lv.style_t()
style_setting_screen_clock_sub_button_main_main_default.init()
style_setting_screen_clock_sub_button_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_setting_screen_clock_sub_button_main_main_default.set_img_recolor_opa(0)
style_setting_screen_clock_sub_button_main_main_default.set_img_opa(255)

# add style for Setting_Screen_Clock_Sub_Button
Setting_Screen_Clock_Sub_Button.add_style(style_setting_screen_clock_sub_button_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

Setting_Screen_Clock_24_hr_NotSet = lv.img(Setting_Screen)
Setting_Screen_Clock_24_hr_NotSet.set_pos(149,206)
Setting_Screen_Clock_24_hr_NotSet.set_size(22,11)
Setting_Screen_Clock_24_hr_NotSet.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp1760126487.png','rb') as f:
        Setting_Screen_Clock_24_hr_NotSet_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp1760126487.png')
    sys.exit()

Setting_Screen_Clock_24_hr_NotSet_img = lv.img_dsc_t({
  'data_size': len(Setting_Screen_Clock_24_hr_NotSet_img_data),
  'header': {'always_zero': 0, 'w': 22, 'h': 11, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': Setting_Screen_Clock_24_hr_NotSet_img_data
})

Setting_Screen_Clock_24_hr_NotSet.set_src(Setting_Screen_Clock_24_hr_NotSet_img)
Setting_Screen_Clock_24_hr_NotSet.set_pivot(0,0)
Setting_Screen_Clock_24_hr_NotSet.set_angle(0)
# create style style_setting_screen_clock_24_hr_notset_main_main_default
style_setting_screen_clock_24_hr_notset_main_main_default = lv.style_t()
style_setting_screen_clock_24_hr_notset_main_main_default.init()
style_setting_screen_clock_24_hr_notset_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_setting_screen_clock_24_hr_notset_main_main_default.set_img_recolor_opa(0)
style_setting_screen_clock_24_hr_notset_main_main_default.set_img_opa(255)

# add style for Setting_Screen_Clock_24_hr_NotSet
Setting_Screen_Clock_24_hr_NotSet.add_style(style_setting_screen_clock_24_hr_notset_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

Setting_Screen_Clock_24_hr_Set = lv.img(Setting_Screen)
Setting_Screen_Clock_24_hr_Set.set_pos(159,207)
Setting_Screen_Clock_24_hr_Set.set_size(18,9)
Setting_Screen_Clock_24_hr_Set.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1562734939.png','rb') as f:
        Setting_Screen_Clock_24_hr_Set_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1562734939.png')
    sys.exit()

Setting_Screen_Clock_24_hr_Set_img = lv.img_dsc_t({
  'data_size': len(Setting_Screen_Clock_24_hr_Set_img_data),
  'header': {'always_zero': 0, 'w': 18, 'h': 9, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': Setting_Screen_Clock_24_hr_Set_img_data
})

Setting_Screen_Clock_24_hr_Set.set_src(Setting_Screen_Clock_24_hr_Set_img)
Setting_Screen_Clock_24_hr_Set.set_pivot(0,0)
Setting_Screen_Clock_24_hr_Set.set_angle(0)
# create style style_setting_screen_clock_24_hr_set_main_main_default
style_setting_screen_clock_24_hr_set_main_main_default = lv.style_t()
style_setting_screen_clock_24_hr_set_main_main_default.init()
style_setting_screen_clock_24_hr_set_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_setting_screen_clock_24_hr_set_main_main_default.set_img_recolor_opa(0)
style_setting_screen_clock_24_hr_set_main_main_default.set_img_opa(255)

# add style for Setting_Screen_Clock_24_hr_Set
Setting_Screen_Clock_24_hr_Set.add_style(style_setting_screen_clock_24_hr_set_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

Setting_Screen_About_Unit = lv.label(Setting_Screen)
Setting_Screen_About_Unit.set_pos(153,101)
Setting_Screen_About_Unit.set_size(64,19)
Setting_Screen_About_Unit.set_text("Aunit")
Setting_Screen_About_Unit.set_long_mode(lv.label.LONG.WRAP)
Setting_Screen_About_Unit.set_style_text_align(lv.TEXT_ALIGN.CENTER, 0)
# create style style_setting_screen_about_unit_main_main_default
style_setting_screen_about_unit_main_main_default = lv.style_t()
style_setting_screen_about_unit_main_main_default.init()
style_setting_screen_about_unit_main_main_default.set_radius(0)
style_setting_screen_about_unit_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_setting_screen_about_unit_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_setting_screen_about_unit_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_setting_screen_about_unit_main_main_default.set_bg_opa(0)
style_setting_screen_about_unit_main_main_default.set_text_color(lv.color_make(0x4d,0x47,0x47))
try:
    style_setting_screen_about_unit_main_main_default.set_text_font(lv.font_FjallaOne_Regular_22)
except AttributeError:
    try:
        style_setting_screen_about_unit_main_main_default.set_text_font(lv.font_montserrat_22)
    except AttributeError:
        style_setting_screen_about_unit_main_main_default.set_text_font(lv.font_montserrat_16)
style_setting_screen_about_unit_main_main_default.set_text_letter_space(0)
style_setting_screen_about_unit_main_main_default.set_pad_left(0)
style_setting_screen_about_unit_main_main_default.set_pad_right(0)
style_setting_screen_about_unit_main_main_default.set_pad_top(0)
style_setting_screen_about_unit_main_main_default.set_pad_bottom(0)

# add style for Setting_Screen_About_Unit
Setting_Screen_About_Unit.add_style(style_setting_screen_about_unit_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

Setting_Screen_Conn_Unit = lv.label(Setting_Screen)
Setting_Screen_Conn_Unit.set_pos(151,148)
Setting_Screen_Conn_Unit.set_size(62,19)
Setting_Screen_Conn_Unit.set_text("Cunit")
Setting_Screen_Conn_Unit.set_long_mode(lv.label.LONG.WRAP)
Setting_Screen_Conn_Unit.set_style_text_align(lv.TEXT_ALIGN.CENTER, 0)
# create style style_setting_screen_conn_unit_main_main_default
style_setting_screen_conn_unit_main_main_default = lv.style_t()
style_setting_screen_conn_unit_main_main_default.init()
style_setting_screen_conn_unit_main_main_default.set_radius(0)
style_setting_screen_conn_unit_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_setting_screen_conn_unit_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_setting_screen_conn_unit_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_setting_screen_conn_unit_main_main_default.set_bg_opa(0)
style_setting_screen_conn_unit_main_main_default.set_text_color(lv.color_make(0x4d,0x47,0x47))
try:
    style_setting_screen_conn_unit_main_main_default.set_text_font(lv.font_FjallaOne_Regular_22)
except AttributeError:
    try:
        style_setting_screen_conn_unit_main_main_default.set_text_font(lv.font_montserrat_22)
    except AttributeError:
        style_setting_screen_conn_unit_main_main_default.set_text_font(lv.font_montserrat_16)
style_setting_screen_conn_unit_main_main_default.set_text_letter_space(0)
style_setting_screen_conn_unit_main_main_default.set_pad_left(0)
style_setting_screen_conn_unit_main_main_default.set_pad_right(0)
style_setting_screen_conn_unit_main_main_default.set_pad_top(0)
style_setting_screen_conn_unit_main_main_default.set_pad_bottom(0)

# add style for Setting_Screen_Conn_Unit
Setting_Screen_Conn_Unit.add_style(style_setting_screen_conn_unit_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

Setting_Screen_Bike_Unit = lv.label(Setting_Screen)
Setting_Screen_Bike_Unit.set_pos(152,196)
Setting_Screen_Bike_Unit.set_size(62,19)
Setting_Screen_Bike_Unit.set_text("Bunit")
Setting_Screen_Bike_Unit.set_long_mode(lv.label.LONG.WRAP)
Setting_Screen_Bike_Unit.set_style_text_align(lv.TEXT_ALIGN.CENTER, 0)
# create style style_setting_screen_bike_unit_main_main_default
style_setting_screen_bike_unit_main_main_default = lv.style_t()
style_setting_screen_bike_unit_main_main_default.init()
style_setting_screen_bike_unit_main_main_default.set_radius(0)
style_setting_screen_bike_unit_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_setting_screen_bike_unit_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_setting_screen_bike_unit_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_setting_screen_bike_unit_main_main_default.set_bg_opa(0)
style_setting_screen_bike_unit_main_main_default.set_text_color(lv.color_make(0x56,0x4d,0x4d))
try:
    style_setting_screen_bike_unit_main_main_default.set_text_font(lv.font_FjallaOne_Regular_22)
except AttributeError:
    try:
        style_setting_screen_bike_unit_main_main_default.set_text_font(lv.font_montserrat_22)
    except AttributeError:
        style_setting_screen_bike_unit_main_main_default.set_text_font(lv.font_montserrat_16)
style_setting_screen_bike_unit_main_main_default.set_text_letter_space(0)
style_setting_screen_bike_unit_main_main_default.set_pad_left(0)
style_setting_screen_bike_unit_main_main_default.set_pad_right(0)
style_setting_screen_bike_unit_main_main_default.set_pad_top(0)
style_setting_screen_bike_unit_main_main_default.set_pad_bottom(0)

# add style for Setting_Screen_Bike_Unit
Setting_Screen_Bike_Unit.add_style(style_setting_screen_bike_unit_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

Setting_Screen_Unit_Icon = lv.img(Setting_Screen)
Setting_Screen_Unit_Icon.set_pos(14,143)
Setting_Screen_Unit_Icon.set_size(30,30)
Setting_Screen_Unit_Icon.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp837254390.png','rb') as f:
        Setting_Screen_Unit_Icon_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp837254390.png')
    sys.exit()

Setting_Screen_Unit_Icon_img = lv.img_dsc_t({
  'data_size': len(Setting_Screen_Unit_Icon_img_data),
  'header': {'always_zero': 0, 'w': 30, 'h': 30, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': Setting_Screen_Unit_Icon_img_data
})

Setting_Screen_Unit_Icon.set_src(Setting_Screen_Unit_Icon_img)
Setting_Screen_Unit_Icon.set_pivot(0,0)
Setting_Screen_Unit_Icon.set_angle(0)
# create style style_setting_screen_unit_icon_main_main_default
style_setting_screen_unit_icon_main_main_default = lv.style_t()
style_setting_screen_unit_icon_main_main_default.init()
style_setting_screen_unit_icon_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_setting_screen_unit_icon_main_main_default.set_img_recolor_opa(0)
style_setting_screen_unit_icon_main_main_default.set_img_opa(0)

# add style for Setting_Screen_Unit_Icon
Setting_Screen_Unit_Icon.add_style(style_setting_screen_unit_icon_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

Setting_Screen_Date_time_Icon = lv.img(Setting_Screen)
Setting_Screen_Date_time_Icon.set_pos(14,143)
Setting_Screen_Date_time_Icon.set_size(30,30)
Setting_Screen_Date_time_Icon.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1445952126.png','rb') as f:
        Setting_Screen_Date_time_Icon_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1445952126.png')
    sys.exit()

Setting_Screen_Date_time_Icon_img = lv.img_dsc_t({
  'data_size': len(Setting_Screen_Date_time_Icon_img_data),
  'header': {'always_zero': 0, 'w': 30, 'h': 30, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': Setting_Screen_Date_time_Icon_img_data
})

Setting_Screen_Date_time_Icon.set_src(Setting_Screen_Date_time_Icon_img)
Setting_Screen_Date_time_Icon.set_pivot(0,0)
Setting_Screen_Date_time_Icon.set_angle(0)
# create style style_setting_screen_date_time_icon_main_main_default
style_setting_screen_date_time_icon_main_main_default = lv.style_t()
style_setting_screen_date_time_icon_main_main_default.init()
style_setting_screen_date_time_icon_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_setting_screen_date_time_icon_main_main_default.set_img_recolor_opa(0)
style_setting_screen_date_time_icon_main_main_default.set_img_opa(0)

# add style for Setting_Screen_Date_time_Icon
Setting_Screen_Date_time_Icon.add_style(style_setting_screen_date_time_icon_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

Setting_Screen_Distance_Icon = lv.img(Setting_Screen)
Setting_Screen_Distance_Icon.set_pos(14,143)
Setting_Screen_Distance_Icon.set_size(30,30)
Setting_Screen_Distance_Icon.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1527833814.png','rb') as f:
        Setting_Screen_Distance_Icon_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1527833814.png')
    sys.exit()

Setting_Screen_Distance_Icon_img = lv.img_dsc_t({
  'data_size': len(Setting_Screen_Distance_Icon_img_data),
  'header': {'always_zero': 0, 'w': 30, 'h': 30, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': Setting_Screen_Distance_Icon_img_data
})

Setting_Screen_Distance_Icon.set_src(Setting_Screen_Distance_Icon_img)
Setting_Screen_Distance_Icon.set_pivot(0,0)
Setting_Screen_Distance_Icon.set_angle(0)
# create style style_setting_screen_distance_icon_main_main_default
style_setting_screen_distance_icon_main_main_default = lv.style_t()
style_setting_screen_distance_icon_main_main_default.init()
style_setting_screen_distance_icon_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_setting_screen_distance_icon_main_main_default.set_img_recolor_opa(0)
style_setting_screen_distance_icon_main_main_default.set_img_opa(0)

# add style for Setting_Screen_Distance_Icon
Setting_Screen_Distance_Icon.add_style(style_setting_screen_distance_icon_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

Setting_Screen_Trip_Icon = lv.img(Setting_Screen)
Setting_Screen_Trip_Icon.set_pos(14,143)
Setting_Screen_Trip_Icon.set_size(30,30)
Setting_Screen_Trip_Icon.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp765003578.png','rb') as f:
        Setting_Screen_Trip_Icon_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp765003578.png')
    sys.exit()

Setting_Screen_Trip_Icon_img = lv.img_dsc_t({
  'data_size': len(Setting_Screen_Trip_Icon_img_data),
  'header': {'always_zero': 0, 'w': 30, 'h': 30, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': Setting_Screen_Trip_Icon_img_data
})

Setting_Screen_Trip_Icon.set_src(Setting_Screen_Trip_Icon_img)
Setting_Screen_Trip_Icon.set_pivot(0,0)
Setting_Screen_Trip_Icon.set_angle(0)
# create style style_setting_screen_trip_icon_main_main_default
style_setting_screen_trip_icon_main_main_default = lv.style_t()
style_setting_screen_trip_icon_main_main_default.init()
style_setting_screen_trip_icon_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_setting_screen_trip_icon_main_main_default.set_img_recolor_opa(0)
style_setting_screen_trip_icon_main_main_default.set_img_opa(0)

# add style for Setting_Screen_Trip_Icon
Setting_Screen_Trip_Icon.add_style(style_setting_screen_trip_icon_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

Setting_Screen_Fuel_Icon = lv.img(Setting_Screen)
Setting_Screen_Fuel_Icon.set_pos(14,143)
Setting_Screen_Fuel_Icon.set_size(30,30)
Setting_Screen_Fuel_Icon.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-887390785.png','rb') as f:
        Setting_Screen_Fuel_Icon_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-887390785.png')
    sys.exit()

Setting_Screen_Fuel_Icon_img = lv.img_dsc_t({
  'data_size': len(Setting_Screen_Fuel_Icon_img_data),
  'header': {'always_zero': 0, 'w': 30, 'h': 30, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': Setting_Screen_Fuel_Icon_img_data
})

Setting_Screen_Fuel_Icon.set_src(Setting_Screen_Fuel_Icon_img)
Setting_Screen_Fuel_Icon.set_pivot(0,0)
Setting_Screen_Fuel_Icon.set_angle(0)
# create style style_setting_screen_fuel_icon_main_main_default
style_setting_screen_fuel_icon_main_main_default = lv.style_t()
style_setting_screen_fuel_icon_main_main_default.init()
style_setting_screen_fuel_icon_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_setting_screen_fuel_icon_main_main_default.set_img_recolor_opa(0)
style_setting_screen_fuel_icon_main_main_default.set_img_opa(0)

# add style for Setting_Screen_Fuel_Icon
Setting_Screen_Fuel_Icon.add_style(style_setting_screen_fuel_icon_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

Setting_Screen_Trip_icon_A = lv.img(Setting_Screen)
Setting_Screen_Trip_icon_A.set_pos(14,143)
Setting_Screen_Trip_icon_A.set_size(30,30)
Setting_Screen_Trip_icon_A.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp739187799.png','rb') as f:
        Setting_Screen_Trip_icon_A_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp739187799.png')
    sys.exit()

Setting_Screen_Trip_icon_A_img = lv.img_dsc_t({
  'data_size': len(Setting_Screen_Trip_icon_A_img_data),
  'header': {'always_zero': 0, 'w': 30, 'h': 30, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': Setting_Screen_Trip_icon_A_img_data
})

Setting_Screen_Trip_icon_A.set_src(Setting_Screen_Trip_icon_A_img)
Setting_Screen_Trip_icon_A.set_pivot(0,0)
Setting_Screen_Trip_icon_A.set_angle(0)
# create style style_setting_screen_trip_icon_a_main_main_default
style_setting_screen_trip_icon_a_main_main_default = lv.style_t()
style_setting_screen_trip_icon_a_main_main_default.init()
style_setting_screen_trip_icon_a_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_setting_screen_trip_icon_a_main_main_default.set_img_recolor_opa(0)
style_setting_screen_trip_icon_a_main_main_default.set_img_opa(0)

# add style for Setting_Screen_Trip_icon_A
Setting_Screen_Trip_icon_A.add_style(style_setting_screen_trip_icon_a_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

Setting_Screen_Connectivity_Icon = lv.img(Setting_Screen)
Setting_Screen_Connectivity_Icon.set_pos(14,143)
Setting_Screen_Connectivity_Icon.set_size(30,30)
Setting_Screen_Connectivity_Icon.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp523267589.png','rb') as f:
        Setting_Screen_Connectivity_Icon_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp523267589.png')
    sys.exit()

Setting_Screen_Connectivity_Icon_img = lv.img_dsc_t({
  'data_size': len(Setting_Screen_Connectivity_Icon_img_data),
  'header': {'always_zero': 0, 'w': 30, 'h': 30, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': Setting_Screen_Connectivity_Icon_img_data
})

Setting_Screen_Connectivity_Icon.set_src(Setting_Screen_Connectivity_Icon_img)
Setting_Screen_Connectivity_Icon.set_pivot(0,0)
Setting_Screen_Connectivity_Icon.set_angle(0)
# create style style_setting_screen_connectivity_icon_main_main_default
style_setting_screen_connectivity_icon_main_main_default = lv.style_t()
style_setting_screen_connectivity_icon_main_main_default.init()
style_setting_screen_connectivity_icon_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_setting_screen_connectivity_icon_main_main_default.set_img_recolor_opa(0)
style_setting_screen_connectivity_icon_main_main_default.set_img_opa(0)

# add style for Setting_Screen_Connectivity_Icon
Setting_Screen_Connectivity_Icon.add_style(style_setting_screen_connectivity_icon_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

Setting_Screen_Hold_Sub_Button = lv.img(Setting_Screen)
Setting_Screen_Hold_Sub_Button.set_pos(79,72)
Setting_Screen_Hold_Sub_Button.set_size(20,20)
Setting_Screen_Hold_Sub_Button.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1198168671.png','rb') as f:
        Setting_Screen_Hold_Sub_Button_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1198168671.png')
    sys.exit()

Setting_Screen_Hold_Sub_Button_img = lv.img_dsc_t({
  'data_size': len(Setting_Screen_Hold_Sub_Button_img_data),
  'header': {'always_zero': 0, 'w': 20, 'h': 20, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': Setting_Screen_Hold_Sub_Button_img_data
})

Setting_Screen_Hold_Sub_Button.set_src(Setting_Screen_Hold_Sub_Button_img)
Setting_Screen_Hold_Sub_Button.set_pivot(0,0)
Setting_Screen_Hold_Sub_Button.set_angle(0)
# create style style_setting_screen_hold_sub_button_main_main_default
style_setting_screen_hold_sub_button_main_main_default = lv.style_t()
style_setting_screen_hold_sub_button_main_main_default.init()
style_setting_screen_hold_sub_button_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_setting_screen_hold_sub_button_main_main_default.set_img_recolor_opa(0)
style_setting_screen_hold_sub_button_main_main_default.set_img_opa(255)

# add style for Setting_Screen_Hold_Sub_Button
Setting_Screen_Hold_Sub_Button.add_style(style_setting_screen_hold_sub_button_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

Setting_Screen_Hold_Sub_Button_Hide = lv.img(Setting_Screen)
Setting_Screen_Hold_Sub_Button_Hide.set_pos(144,69)
Setting_Screen_Hold_Sub_Button_Hide.set_size(20,20)
Setting_Screen_Hold_Sub_Button_Hide.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1198168671.png','rb') as f:
        Setting_Screen_Hold_Sub_Button_Hide_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1198168671.png')
    sys.exit()

Setting_Screen_Hold_Sub_Button_Hide_img = lv.img_dsc_t({
  'data_size': len(Setting_Screen_Hold_Sub_Button_Hide_img_data),
  'header': {'always_zero': 0, 'w': 20, 'h': 20, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': Setting_Screen_Hold_Sub_Button_Hide_img_data
})

Setting_Screen_Hold_Sub_Button_Hide.set_src(Setting_Screen_Hold_Sub_Button_Hide_img)
Setting_Screen_Hold_Sub_Button_Hide.set_pivot(0,0)
Setting_Screen_Hold_Sub_Button_Hide.set_angle(0)
# create style style_setting_screen_hold_sub_button_hide_main_main_default
style_setting_screen_hold_sub_button_hide_main_main_default = lv.style_t()
style_setting_screen_hold_sub_button_hide_main_main_default.init()
style_setting_screen_hold_sub_button_hide_main_main_default.set_img_recolor(lv.color_make(0x56,0x4d,0x4d))
style_setting_screen_hold_sub_button_hide_main_main_default.set_img_recolor_opa(0)
style_setting_screen_hold_sub_button_hide_main_main_default.set_img_opa(51)

# add style for Setting_Screen_Hold_Sub_Button_Hide
Setting_Screen_Hold_Sub_Button_Hide.add_style(style_setting_screen_hold_sub_button_hide_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

Setting_Screen_Bluetooth_Icon = lv.img(Setting_Screen)
Setting_Screen_Bluetooth_Icon.set_pos(14,143)
Setting_Screen_Bluetooth_Icon.set_size(30,30)
Setting_Screen_Bluetooth_Icon.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1372034950.png','rb') as f:
        Setting_Screen_Bluetooth_Icon_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1372034950.png')
    sys.exit()

Setting_Screen_Bluetooth_Icon_img = lv.img_dsc_t({
  'data_size': len(Setting_Screen_Bluetooth_Icon_img_data),
  'header': {'always_zero': 0, 'w': 30, 'h': 30, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': Setting_Screen_Bluetooth_Icon_img_data
})

Setting_Screen_Bluetooth_Icon.set_src(Setting_Screen_Bluetooth_Icon_img)
Setting_Screen_Bluetooth_Icon.set_pivot(0,0)
Setting_Screen_Bluetooth_Icon.set_angle(0)
# create style style_setting_screen_bluetooth_icon_main_main_default
style_setting_screen_bluetooth_icon_main_main_default = lv.style_t()
style_setting_screen_bluetooth_icon_main_main_default.init()
style_setting_screen_bluetooth_icon_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_setting_screen_bluetooth_icon_main_main_default.set_img_recolor_opa(0)
style_setting_screen_bluetooth_icon_main_main_default.set_img_opa(0)

# add style for Setting_Screen_Bluetooth_Icon
Setting_Screen_Bluetooth_Icon.add_style(style_setting_screen_bluetooth_icon_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

Setting_Screen_On_Btn = lv.img(Setting_Screen)
Setting_Screen_On_Btn.set_pos(179,152)
Setting_Screen_On_Btn.set_size(29,20)
Setting_Screen_On_Btn.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp824416276.png','rb') as f:
        Setting_Screen_On_Btn_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp824416276.png')
    sys.exit()

Setting_Screen_On_Btn_img = lv.img_dsc_t({
  'data_size': len(Setting_Screen_On_Btn_img_data),
  'header': {'always_zero': 0, 'w': 29, 'h': 20, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': Setting_Screen_On_Btn_img_data
})

Setting_Screen_On_Btn.set_src(Setting_Screen_On_Btn_img)
Setting_Screen_On_Btn.set_pivot(0,0)
Setting_Screen_On_Btn.set_angle(0)
# create style style_setting_screen_on_btn_main_main_default
style_setting_screen_on_btn_main_main_default = lv.style_t()
style_setting_screen_on_btn_main_main_default.init()
style_setting_screen_on_btn_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_setting_screen_on_btn_main_main_default.set_img_recolor_opa(0)
style_setting_screen_on_btn_main_main_default.set_img_opa(0)

# add style for Setting_Screen_On_Btn
Setting_Screen_On_Btn.add_style(style_setting_screen_on_btn_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

Setting_Screen_Off_Btn = lv.img(Setting_Screen)
Setting_Screen_Off_Btn.set_pos(179,193)
Setting_Screen_Off_Btn.set_size(29,20)
Setting_Screen_Off_Btn.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-826988994.png','rb') as f:
        Setting_Screen_Off_Btn_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-826988994.png')
    sys.exit()

Setting_Screen_Off_Btn_img = lv.img_dsc_t({
  'data_size': len(Setting_Screen_Off_Btn_img_data),
  'header': {'always_zero': 0, 'w': 29, 'h': 20, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': Setting_Screen_Off_Btn_img_data
})

Setting_Screen_Off_Btn.set_src(Setting_Screen_Off_Btn_img)
Setting_Screen_Off_Btn.set_pivot(0,0)
Setting_Screen_Off_Btn.set_angle(0)
# create style style_setting_screen_off_btn_main_main_default
style_setting_screen_off_btn_main_main_default = lv.style_t()
style_setting_screen_off_btn_main_main_default.init()
style_setting_screen_off_btn_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_setting_screen_off_btn_main_main_default.set_img_recolor_opa(0)
style_setting_screen_off_btn_main_main_default.set_img_opa(0)

# add style for Setting_Screen_Off_Btn
Setting_Screen_Off_Btn.add_style(style_setting_screen_off_btn_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

Setting_Screen_Off_Btn1 = lv.img(Setting_Screen)
Setting_Screen_Off_Btn1.set_pos(179,102)
Setting_Screen_Off_Btn1.set_size(29,20)
Setting_Screen_Off_Btn1.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-826988994.png','rb') as f:
        Setting_Screen_Off_Btn1_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-826988994.png')
    sys.exit()

Setting_Screen_Off_Btn1_img = lv.img_dsc_t({
  'data_size': len(Setting_Screen_Off_Btn1_img_data),
  'header': {'always_zero': 0, 'w': 29, 'h': 20, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': Setting_Screen_Off_Btn1_img_data
})

Setting_Screen_Off_Btn1.set_src(Setting_Screen_Off_Btn1_img)
Setting_Screen_Off_Btn1.set_pivot(0,0)
Setting_Screen_Off_Btn1.set_angle(0)
# create style style_setting_screen_off_btn1_main_main_default
style_setting_screen_off_btn1_main_main_default = lv.style_t()
style_setting_screen_off_btn1_main_main_default.init()
style_setting_screen_off_btn1_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_setting_screen_off_btn1_main_main_default.set_img_recolor_opa(0)
style_setting_screen_off_btn1_main_main_default.set_img_opa(0)

# add style for Setting_Screen_Off_Btn1
Setting_Screen_Off_Btn1.add_style(style_setting_screen_off_btn1_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

Setting_Screen_Middle_Label_New = lv.label(Setting_Screen)
Setting_Screen_Middle_Label_New.set_pos(57,148)
Setting_Screen_Middle_Label_New.set_size(132,18)
Setting_Screen_Middle_Label_New.set_text("CO NNECTIVITY")
Setting_Screen_Middle_Label_New.set_long_mode(lv.label.LONG.CLIP)
Setting_Screen_Middle_Label_New.set_style_text_align(lv.TEXT_ALIGN.CENTER, 0)
# create style style_setting_screen_middle_label_new_main_main_default
style_setting_screen_middle_label_new_main_main_default = lv.style_t()
style_setting_screen_middle_label_new_main_main_default.init()
style_setting_screen_middle_label_new_main_main_default.set_radius(0)
style_setting_screen_middle_label_new_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_setting_screen_middle_label_new_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_setting_screen_middle_label_new_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_setting_screen_middle_label_new_main_main_default.set_bg_opa(0)
style_setting_screen_middle_label_new_main_main_default.set_text_color(lv.color_make(0xf6,0xf4,0xf4))
try:
    style_setting_screen_middle_label_new_main_main_default.set_text_font(lv.font_FjallaOne_Regular_22)
except AttributeError:
    try:
        style_setting_screen_middle_label_new_main_main_default.set_text_font(lv.font_montserrat_22)
    except AttributeError:
        style_setting_screen_middle_label_new_main_main_default.set_text_font(lv.font_montserrat_16)
style_setting_screen_middle_label_new_main_main_default.set_text_letter_space(0)
style_setting_screen_middle_label_new_main_main_default.set_pad_left(0)
style_setting_screen_middle_label_new_main_main_default.set_pad_right(0)
style_setting_screen_middle_label_new_main_main_default.set_pad_top(0)
style_setting_screen_middle_label_new_main_main_default.set_pad_bottom(0)

# add style for Setting_Screen_Middle_Label_New
Setting_Screen_Middle_Label_New.add_style(style_setting_screen_middle_label_new_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

Setting_Screen_to_save_text = lv.label(Setting_Screen)
Setting_Screen_to_save_text.set_pos(120,226)
Setting_Screen_to_save_text.set_size(65,14)
Setting_Screen_to_save_text.set_text("to SET")
Setting_Screen_to_save_text.set_long_mode(lv.label.LONG.WRAP)
Setting_Screen_to_save_text.set_style_text_align(lv.TEXT_ALIGN.CENTER, 0)
# create style style_setting_screen_to_save_text_main_main_default
style_setting_screen_to_save_text_main_main_default = lv.style_t()
style_setting_screen_to_save_text_main_main_default.init()
style_setting_screen_to_save_text_main_main_default.set_radius(0)
style_setting_screen_to_save_text_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_setting_screen_to_save_text_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_setting_screen_to_save_text_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_setting_screen_to_save_text_main_main_default.set_bg_opa(0)
style_setting_screen_to_save_text_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_setting_screen_to_save_text_main_main_default.set_text_font(lv.font_FjallaOne_Regular_16)
except AttributeError:
    try:
        style_setting_screen_to_save_text_main_main_default.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_setting_screen_to_save_text_main_main_default.set_text_font(lv.font_montserrat_16)
style_setting_screen_to_save_text_main_main_default.set_text_letter_space(0)
style_setting_screen_to_save_text_main_main_default.set_pad_left(0)
style_setting_screen_to_save_text_main_main_default.set_pad_right(0)
style_setting_screen_to_save_text_main_main_default.set_pad_top(0)
style_setting_screen_to_save_text_main_main_default.set_pad_bottom(0)

# add style for Setting_Screen_to_save_text
Setting_Screen_to_save_text.add_style(style_setting_screen_to_save_text_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

Setting_Screen_Set_text = lv.label(Setting_Screen)
Setting_Screen_Set_text.set_pos(94,163)
Setting_Screen_Set_text.set_size(70,20)
Setting_Screen_Set_text.set_text("set ault")
Setting_Screen_Set_text.set_long_mode(lv.label.LONG.WRAP)
Setting_Screen_Set_text.set_style_text_align(lv.TEXT_ALIGN.CENTER, 0)
# create style style_setting_screen_set_text_main_main_default
style_setting_screen_set_text_main_main_default = lv.style_t()
style_setting_screen_set_text_main_main_default.init()
style_setting_screen_set_text_main_main_default.set_radius(0)
style_setting_screen_set_text_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_setting_screen_set_text_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_setting_screen_set_text_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_setting_screen_set_text_main_main_default.set_bg_opa(0)
style_setting_screen_set_text_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_setting_screen_set_text_main_main_default.set_text_font(lv.font_FjallaOne_Regular_16)
except AttributeError:
    try:
        style_setting_screen_set_text_main_main_default.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_setting_screen_set_text_main_main_default.set_text_font(lv.font_montserrat_16)
style_setting_screen_set_text_main_main_default.set_text_letter_space(0)
style_setting_screen_set_text_main_main_default.set_pad_left(0)
style_setting_screen_set_text_main_main_default.set_pad_right(0)
style_setting_screen_set_text_main_main_default.set_pad_top(0)
style_setting_screen_set_text_main_main_default.set_pad_bottom(0)

# add style for Setting_Screen_Set_text
Setting_Screen_Set_text.add_style(style_setting_screen_set_text_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

Setting_Screen_Display_Image = lv.img(Setting_Screen)
Setting_Screen_Display_Image.set_pos(14,143)
Setting_Screen_Display_Image.set_size(30,30)
Setting_Screen_Display_Image.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1995568010.png','rb') as f:
        Setting_Screen_Display_Image_img_data = f.read()
except:
    print('Could not open F:\\Santhosh\\New84Image\\raaa\\generated\\mp-1995568010.png')
    sys.exit()

Setting_Screen_Display_Image_img = lv.img_dsc_t({
  'data_size': len(Setting_Screen_Display_Image_img_data),
  'header': {'always_zero': 0, 'w': 30, 'h': 30, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': Setting_Screen_Display_Image_img_data
})

Setting_Screen_Display_Image.set_src(Setting_Screen_Display_Image_img)
Setting_Screen_Display_Image.set_pivot(0,0)
Setting_Screen_Display_Image.set_angle(0)
# create style style_setting_screen_display_image_main_main_default
style_setting_screen_display_image_main_main_default = lv.style_t()
style_setting_screen_display_image_main_main_default.init()
style_setting_screen_display_image_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_setting_screen_display_image_main_main_default.set_img_recolor_opa(0)
style_setting_screen_display_image_main_main_default.set_img_opa(0)

# add style for Setting_Screen_Display_Image
Setting_Screen_Display_Image.add_style(style_setting_screen_display_image_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)




# content from custom.py

# Load the default screen
lv.scr_load(Main_Screen)

while SDL.check():
    time.sleep_ms(5)
