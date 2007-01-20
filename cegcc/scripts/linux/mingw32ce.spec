Summary:	CeGCC offers cross-development to create Windows CE apps for ARM processors
Name:		cegcc-mingw32ce
%define version 0.12
Version:	0.12
Release:	1
License:	open
Packager:	Danny Backx <dannybackx@users.sourceforge.net>
Group:		Development/Tools
Prefix:		/opt/mingw32ce
# Source:		http://sourceforge.net/project/showfiles.php?group_id=173455
Source:		/tmp/cegcc-mingw32ce-src-%{version}.tar.gz
BuildRoot:	%{_tmppath}/%{name}-buildroot

%description
CeGCC

%prep
%setup -q
# %setup -n cegcc-minge32ce-0.12

%build
rm -rf $RPM_BUILD_ROOT
export PREFIX=/opt/mingw32ce
cd src || exit 1
# sh build-cegcc.sh . $RPM_BUILD_ROOT $PREFIX all || exit 1
sh build-mingw32ce.sh all || exit 1

%install
cd /
rm -rf $RPM_BUILD_ROOT
mkdir $RPM_BUILD_ROOT
tar cf - opt/mingw32ce | (cd $RPM_BUILD_ROOT; tar xf -)

%clean
rm -rf $RPM_BUILD_ROOT

%files
/opt/mingw32ce
#/opt/cegcc/arm-wince-cegcc
#%attr(755, root, root) /opt/cegcc/bin
#/opt/cegcc/include
#/opt/cegcc/lib
#/opt/cegcc/libexec
#/opt/cegcc/share
#/opt/cegcc/COPYING
#/opt/cegcc/COPYING.LIB
#/opt/cegcc/NEWS
#/opt/cegcc/README

%changelog
* Sat Jan 20 2007 Danny Backx <dannybackx@users.sf.net>
- Copy cegcc.spec into mingw32ce.spec, change the stuff that's required.

* Sat Dec 31 2006 Danny Backx <dannybackx@users.sf.net>
- Strip out mingw32ce.

* Sat Dec 30 2006 Danny Backx <dannybackx@users.sf.net>
- Adapt to Pedro's build scripts and /opt/cegcc and /opt/mingw32ce .

* Wed Nov 1 2006 Danny Backx <dannybackx@users.sf.net>
- Add COPYING.LIB
- Increase level to produce a 0.11 version next time.

* Wed Oct 11 2006 Danny Backx <dannybackx@users.sf.net>
- Add a couple of text files.

* Sat Oct 7 2006 Danny Backx <dannybackx@users.sf.net>
- Change to implement arm-wince-cegcc and arm-wince-mingw32ce targets.

* Sun Sep 17 2006 Danny Backx <dannybackx@users.sf.net>
- Add documentation files.

* Thu Sep 14 2006 Danny Backx <dannybackx@users.sf.net>
- Fix the path in install so we don't need to have cegcc installed to be
  able to run rpmbuild.

* Sun Sep 3 2006 Danny Backx <dannybackx@users.sf.net>
- initial version of the spec file.
