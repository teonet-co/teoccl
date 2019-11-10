include aminclude.am
if DX_COND_html

teoccldatarootdocdir = $(datarootdir)/doc/@PACKAGE@
doxydocdir = $(datarootdir)/doc/@PACKAGE@/html
doxydoc_DATA = @DOLLAR_SIGN@(wildcard docs/html/*.*)

doxydoc_searchdir = $(datarootdir)/doc/@PACKAGE@/html/search
doxydoc_search_DATA = @DOLLAR_SIGN@(wildcard docs/html/search/*.*)

DX_CLEANFILES = -rf @DX_DOCDIR@

endif


ACLOCAL_AMFLAGS = -I m4
SUBDIRS = src tools tests
pkgconfig_DATA = src/libteoccl-$(API_VERSION).pc


teoccldocdir = ${prefix}/doc/@PACKAGE@
teoccldoc_DATA = ChangeLog

EXTRA_DIST = $(teoccldoc_DATA) \
	$(INTLTOOL_FILES)

# Remove doc directory on uninstall
uninstall-local:
	-rm -r $(teoccldocdir)
	
test:	
	tests/teoccl_tst 
	tests/teoccl_cpp_tst
