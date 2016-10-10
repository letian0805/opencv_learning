env = Environment()
env["CPPPATH"] = ["/usr/include/opencv"]
env["LIBS"] = ["opencv_core", "opencv_highgui", "m"]
Export("env")

SConscript("img/SConscript")
SConscript("video/SConscript")
