@echo off
call ceedling clobber
call ceedling
ctags --fields=+l --langmap=c:.c.h -R *.c *.h

