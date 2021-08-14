obj = main.obj generate.obj
bin = generate.exe

CPP = wpp386
CXXFLAGS = -fpc -otexan -oh -oi -ei -bt=DOS
LD = wlink

$(bin): $(obj)
    $(LD) name $@ file { *.obj } $(LDFLAGS)

.cpp.obj: .autodepend
    $(CPP) $(CXXFLAGS) $<

clean: .symbolic
    del *.obj
    del *.err
    del $(bin)
