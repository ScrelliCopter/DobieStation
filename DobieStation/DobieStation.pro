TEMPLATE = subdirs
SUBDIRS = application libdeflate fmt

application.depends = libdeflate fmt
