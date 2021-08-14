obj = main.obj video.obj timer.obj mathutil.obj d_roto.obj fx_roto.obj fx_plasm.obj drawtext.obj
bin = demo.exe

CC = wpp
CXXFLAGS = -0 -fpc -otexan -oh -oi -ei -bt=DOS
LD = wlink

$(bin): $(obj)
    $(LD) name $@ file { *.obj } $(LDFLAGS)

.cpp.obj: .autodepend
    $(CC) $(CXXFLAGS) $<

clean: .symbolic
    del *.obj
    del *.err
    del $(bin)
