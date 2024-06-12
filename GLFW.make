# Alternative GNU Make project makefile autogenerated by Premake

ifndef config
  config=debug
endif

ifndef verbose
  SILENT = @
endif

.PHONY: clean prebuild

SHELLTYPE := posix
ifeq (.exe,$(findstring .exe,$(ComSpec)))
	SHELLTYPE := msdos
endif

# Configurations
# #############################################

RESCOMP = windres
TARGETDIR = external/glfw/lib
TARGET = $(TARGETDIR)/glfw3.lib
DEFINES += -D_GLFW_WIN32 -D_GLFW_WGL
INCLUDES += -Iexternal/glfw/include
FORCE_INCLUDE +=
ALL_CPPFLAGS += $(CPPFLAGS) -MD -MP $(DEFINES) $(INCLUDES)
ALL_CFLAGS += $(CFLAGS) $(ALL_CPPFLAGS)
ALL_CXXFLAGS += $(CXXFLAGS) $(ALL_CPPFLAGS)
ALL_RESFLAGS += $(RESFLAGS) $(DEFINES) $(INCLUDES)
LIBS +=
LDDEPS +=
ALL_LDFLAGS += $(LDFLAGS) -s
LINKCMD = $(AR) -rcs "$@" $(OBJECTS)
define PREBUILDCMDS
endef
define PRELINKCMDS
endef
define POSTBUILDCMDS
endef

ifeq ($(config),debug)
OBJDIR = obj/Debug/GLFW

else ifeq ($(config),release)
OBJDIR = obj/Release/GLFW

endif

# Per File Configurations
# #############################################


# File sets
# #############################################

GENERATED :=
OBJECTS :=

GENERATED += $(OBJDIR)/cocoa_time.o
GENERATED += $(OBJDIR)/context.o
GENERATED += $(OBJDIR)/egl_context.o
GENERATED += $(OBJDIR)/glx_context.o
GENERATED += $(OBJDIR)/init.o
GENERATED += $(OBJDIR)/input.o
GENERATED += $(OBJDIR)/linux_joystick.o
GENERATED += $(OBJDIR)/monitor.o
GENERATED += $(OBJDIR)/null_init.o
GENERATED += $(OBJDIR)/null_joystick.o
GENERATED += $(OBJDIR)/null_monitor.o
GENERATED += $(OBJDIR)/null_window.o
GENERATED += $(OBJDIR)/osmesa_context.o
GENERATED += $(OBJDIR)/platform.o
GENERATED += $(OBJDIR)/posix_module.o
GENERATED += $(OBJDIR)/posix_poll.o
GENERATED += $(OBJDIR)/posix_thread.o
GENERATED += $(OBJDIR)/posix_time.o
GENERATED += $(OBJDIR)/vulkan.o
GENERATED += $(OBJDIR)/wgl_context.o
GENERATED += $(OBJDIR)/win32_init.o
GENERATED += $(OBJDIR)/win32_joystick.o
GENERATED += $(OBJDIR)/win32_module.o
GENERATED += $(OBJDIR)/win32_monitor.o
GENERATED += $(OBJDIR)/win32_thread.o
GENERATED += $(OBJDIR)/win32_time.o
GENERATED += $(OBJDIR)/win32_window.o
GENERATED += $(OBJDIR)/window.o
GENERATED += $(OBJDIR)/wl_init.o
GENERATED += $(OBJDIR)/wl_monitor.o
GENERATED += $(OBJDIR)/wl_window.o
GENERATED += $(OBJDIR)/x11_init.o
GENERATED += $(OBJDIR)/x11_monitor.o
GENERATED += $(OBJDIR)/x11_window.o
GENERATED += $(OBJDIR)/xkb_unicode.o
OBJECTS += $(OBJDIR)/cocoa_time.o
OBJECTS += $(OBJDIR)/context.o
OBJECTS += $(OBJDIR)/egl_context.o
OBJECTS += $(OBJDIR)/glx_context.o
OBJECTS += $(OBJDIR)/init.o
OBJECTS += $(OBJDIR)/input.o
OBJECTS += $(OBJDIR)/linux_joystick.o
OBJECTS += $(OBJDIR)/monitor.o
OBJECTS += $(OBJDIR)/null_init.o
OBJECTS += $(OBJDIR)/null_joystick.o
OBJECTS += $(OBJDIR)/null_monitor.o
OBJECTS += $(OBJDIR)/null_window.o
OBJECTS += $(OBJDIR)/osmesa_context.o
OBJECTS += $(OBJDIR)/platform.o
OBJECTS += $(OBJDIR)/posix_module.o
OBJECTS += $(OBJDIR)/posix_poll.o
OBJECTS += $(OBJDIR)/posix_thread.o
OBJECTS += $(OBJDIR)/posix_time.o
OBJECTS += $(OBJDIR)/vulkan.o
OBJECTS += $(OBJDIR)/wgl_context.o
OBJECTS += $(OBJDIR)/win32_init.o
OBJECTS += $(OBJDIR)/win32_joystick.o
OBJECTS += $(OBJDIR)/win32_module.o
OBJECTS += $(OBJDIR)/win32_monitor.o
OBJECTS += $(OBJDIR)/win32_thread.o
OBJECTS += $(OBJDIR)/win32_time.o
OBJECTS += $(OBJDIR)/win32_window.o
OBJECTS += $(OBJDIR)/window.o
OBJECTS += $(OBJDIR)/wl_init.o
OBJECTS += $(OBJDIR)/wl_monitor.o
OBJECTS += $(OBJDIR)/wl_window.o
OBJECTS += $(OBJDIR)/x11_init.o
OBJECTS += $(OBJDIR)/x11_monitor.o
OBJECTS += $(OBJDIR)/x11_window.o
OBJECTS += $(OBJDIR)/xkb_unicode.o

# Rules
# #############################################

all: $(TARGET)
	@:

$(TARGET): $(GENERATED) $(OBJECTS) $(LDDEPS) | $(TARGETDIR)
	$(PRELINKCMDS)
	@echo Linking GLFW
	$(SILENT) $(LINKCMD)
	$(POSTBUILDCMDS)

$(TARGETDIR):
	@echo Creating $(TARGETDIR)
ifeq (posix,$(SHELLTYPE))
	$(SILENT) mkdir -p $(TARGETDIR)
else
	$(SILENT) mkdir $(subst /,\\,$(TARGETDIR))
endif

$(OBJDIR):
	@echo Creating $(OBJDIR)
ifeq (posix,$(SHELLTYPE))
	$(SILENT) mkdir -p $(OBJDIR)
else
	$(SILENT) mkdir $(subst /,\\,$(OBJDIR))
endif

clean:
	@echo Cleaning GLFW
ifeq (posix,$(SHELLTYPE))
	$(SILENT) rm -f  $(TARGET)
	$(SILENT) rm -rf $(GENERATED)
	$(SILENT) rm -rf $(OBJDIR)
else
	$(SILENT) if exist $(subst /,\\,$(TARGET)) del $(subst /,\\,$(TARGET))
	$(SILENT) if exist $(subst /,\\,$(GENERATED)) del /s /q $(subst /,\\,$(GENERATED))
	$(SILENT) if exist $(subst /,\\,$(OBJDIR)) rmdir /s /q $(subst /,\\,$(OBJDIR))
endif

prebuild: | $(OBJDIR)
	$(PREBUILDCMDS)

ifneq (,$(PCH))
$(OBJECTS): $(GCH) | $(PCH_PLACEHOLDER)
$(GCH): $(PCH) | prebuild
	@echo $(notdir $<)
	$(SILENT) $(CC) -x c-header $(ALL_CFLAGS) -o "$@" -MF "$(@:%.gch=%.d)" -c "$<"
$(PCH_PLACEHOLDER): $(GCH) | $(OBJDIR)
ifeq (posix,$(SHELLTYPE))
	$(SILENT) touch "$@"
else
	$(SILENT) echo $null >> "$@"
endif
else
$(OBJECTS): | prebuild
endif


# File Rules
# #############################################

$(OBJDIR)/cocoa_time.o: external/glfw/src/cocoa_time.c
	@echo "$(notdir $<)"
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/context.o: external/glfw/src/context.c
	@echo "$(notdir $<)"
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/egl_context.o: external/glfw/src/egl_context.c
	@echo "$(notdir $<)"
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/glx_context.o: external/glfw/src/glx_context.c
	@echo "$(notdir $<)"
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/init.o: external/glfw/src/init.c
	@echo "$(notdir $<)"
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/input.o: external/glfw/src/input.c
	@echo "$(notdir $<)"
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/linux_joystick.o: external/glfw/src/linux_joystick.c
	@echo "$(notdir $<)"
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/monitor.o: external/glfw/src/monitor.c
	@echo "$(notdir $<)"
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/null_init.o: external/glfw/src/null_init.c
	@echo "$(notdir $<)"
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/null_joystick.o: external/glfw/src/null_joystick.c
	@echo "$(notdir $<)"
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/null_monitor.o: external/glfw/src/null_monitor.c
	@echo "$(notdir $<)"
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/null_window.o: external/glfw/src/null_window.c
	@echo "$(notdir $<)"
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/osmesa_context.o: external/glfw/src/osmesa_context.c
	@echo "$(notdir $<)"
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/platform.o: external/glfw/src/platform.c
	@echo "$(notdir $<)"
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/posix_module.o: external/glfw/src/posix_module.c
	@echo "$(notdir $<)"
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/posix_poll.o: external/glfw/src/posix_poll.c
	@echo "$(notdir $<)"
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/posix_thread.o: external/glfw/src/posix_thread.c
	@echo "$(notdir $<)"
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/posix_time.o: external/glfw/src/posix_time.c
	@echo "$(notdir $<)"
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/vulkan.o: external/glfw/src/vulkan.c
	@echo "$(notdir $<)"
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/wgl_context.o: external/glfw/src/wgl_context.c
	@echo "$(notdir $<)"
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/win32_init.o: external/glfw/src/win32_init.c
	@echo "$(notdir $<)"
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/win32_joystick.o: external/glfw/src/win32_joystick.c
	@echo "$(notdir $<)"
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/win32_module.o: external/glfw/src/win32_module.c
	@echo "$(notdir $<)"
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/win32_monitor.o: external/glfw/src/win32_monitor.c
	@echo "$(notdir $<)"
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/win32_thread.o: external/glfw/src/win32_thread.c
	@echo "$(notdir $<)"
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/win32_time.o: external/glfw/src/win32_time.c
	@echo "$(notdir $<)"
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/win32_window.o: external/glfw/src/win32_window.c
	@echo "$(notdir $<)"
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/window.o: external/glfw/src/window.c
	@echo "$(notdir $<)"
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/wl_init.o: external/glfw/src/wl_init.c
	@echo "$(notdir $<)"
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/wl_monitor.o: external/glfw/src/wl_monitor.c
	@echo "$(notdir $<)"
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/wl_window.o: external/glfw/src/wl_window.c
	@echo "$(notdir $<)"
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/x11_init.o: external/glfw/src/x11_init.c
	@echo "$(notdir $<)"
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/x11_monitor.o: external/glfw/src/x11_monitor.c
	@echo "$(notdir $<)"
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/x11_window.o: external/glfw/src/x11_window.c
	@echo "$(notdir $<)"
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/xkb_unicode.o: external/glfw/src/xkb_unicode.c
	@echo "$(notdir $<)"
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"

-include $(OBJECTS:%.o=%.d)
ifneq (,$(PCH))
  -include $(PCH_PLACEHOLDER).d
endif