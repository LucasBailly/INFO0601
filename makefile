#
# CONFIGURATION GENERALE
#

EXEC = editeur
OBJECTS = functions.o window.o colors.o case.o level.o tableAdresse.o
NOM_PROJET = jeu_editeur

#
# SUFFIXES
#

.SUFFIXES: .c .o

#
# OBJETS
#

EXEC_O = $(EXEC:=.o)
OBJECTS_O = $(OBJECTS) $(EXEC_O)

#
# ARGUMENTS ET COMPILATEUR
#

CC = gcc
CCFLAGS_STD = -Wall -O3 -Werror
CCFLAGS_DEBUG = -D _DEBUG_
CCFLAGS = $(CCFLAGS_STD)
CCLIBS = -lncurses

#
# REGLES
#

all: msg $(OBJECTS) $(EXEC_O)
	@echo "Creation des executables..."
	@for i in $(EXEC); do \
	$(CC) -o $$i $$i.o $(OBJECTS) $(CCLIBS); \
	done
	@echo "Termine."

msg:
	@echo "Creation des objets..."

debug: CCFLAGS = $(CCFLAGS_STD) $(CCFLAGS_DEBUG)
debug: all

#
# REGLES PAR DEFAUT
#

%.o : %.c
	@cd $(dir $<) && ${CC} ${CCFLAGS} -c $(notdir $<) -o $(notdir $@)

#
# REGLES GENERALES
#

clean:
	@echo "Suppresion des objets, des fichiers temporaires..."
	@rm -f $(OBJECTS) $(EXEC_O)
	@rm -f *~ *#
	@rm -f $(EXEC)
	@rm -f dependances
	@echo "Termine."

depend:
	@echo "Creation des dependances..."
	@sed -e "/^# DEPENDANCES/,$$ d" makefile > dependances
	@echo "# DEPENDANCES" >> dependances
	@for i in $(OBJECTS_O); do \
	$(CC) -MM -MT $$i $(CCFLAGS) `echo $$i | sed "s/\(.*\)\\.o$$/\1.c/"` >> dependances; \
	done
	@cat dependances > makefile
	@rm dependances
	@echo "Termine."

#
# CREATION ARCHIVE
#

ARCHIVE_FILES = *

archive: clean
	@echo "Creation de l'archive $(NOM_PROJET)$(shell date '+%y%m%d.tar.gz')..."
	@REP=`basename "$$PWD"`; cd .. && tar zcf $(NOM_PROJET)$(shell date '+%y%m%d.tar.gz') $(addprefix "$$REP"/,$(ARCHIVE_FILES))
	@echo "Termine."

# DEPENDANCES
functions.o: functions.c functions.h
window.o: window.c window.h
colors.o: colors.c colors.h
case.o: case.c case.h colors.h
level.o: level.c level.h case.h
tableAdresse.o: tableAdresse.c tableAdresse.h level.h case.h
editeur.o: editeur.c functions.h window.h colors.h tableAdresse.h level.h \
 case.h
