// Documentation for making Ruby extensions: http://docs.ruby-lang.org/en/2.2.0/README_EXT.html
#include <ruby.h>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>

#include <stdio.h>

#define DECLARE_TYPE(x)			\
    extern "C" VALUE cls ## x;		\
    VALUE cls ## x;

extern "C" VALUE Module; VALUE Module;
DECLARE_TYPE(Widget);
DECLARE_TYPE(Window);

VALUE flWindow_initialize(VALUE self, VALUE width, VALUE height) {
    Check_Type(width,  T_FIXNUM);
    Check_Type(height, T_FIXNUM);
    Fl_Window* wnd = new Fl_Window(width, height);
    // TODO: the following might cause memory leaks.
    VALUE v_inst = Data_Wrap_Struct(clsWindow, 0, -1, wnd);
    rb_iv_set(self, "inst", v_inst);
    return self;
}

VALUE flWidget_show(VALUE self) {
    VALUE v_inst = rb_iv_get(self, "inst");
    Fl_Widget* obj = (Fl_Widget*)malloc(sizeof(Fl_Widget));
    Data_Get_Struct(v_inst, Fl_Widget, obj);
    obj->show();
    return Qnil;
}

VALUE flRun() {
    Fl::run();
}

extern "C" void Init_ntk() {
    Module = rb_define_module("Ntk");
    VALUE clsWidget = rb_define_class_under(Module, "Widget", rb_cObject);
    clsWindow = rb_define_class_under(Module, "Window", clsWidget);
    rb_define_method(clsWindow, "initialize", RUBY_METHOD_FUNC(flWindow_initialize), 2);
    rb_define_method(clsWidget, "show", RUBY_METHOD_FUNC(flWidget_show), 0);
    rb_define_module_function(Module, "run", RUBY_METHOD_FUNC(flRun), 0);
}

