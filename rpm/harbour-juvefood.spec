# 
# Do NOT Edit the Auto-generated Part!
# Generated by: spectacle version 0.27
# 

Name:       harbour-juvefood

# >> macros
# << macros

%{!?qtc_qmake:%define qtc_qmake %qmake}
%{!?qtc_qmake5:%define qtc_qmake5 %qmake5}
%{!?qtc_make:%define qtc_make make}
%{?qtc_builddir:%define _builddir %qtc_builddir}
Summary:    Juvenes food application.
Version:    1.0
Release:    0
Group:      Qt/Qt
License:    The MIT License (MIT)
URL:        http://example.org/
Source0:    %{name}-%{version}.tar.bz2
Source100:  harbour-juvefood.yaml
Requires:   sailfishsilica-qt5 >= 0.10.9
BuildRequires:  pkgconfig(Qt5Quick)
BuildRequires:  pkgconfig(Qt5Qml)
BuildRequires:  pkgconfig(Qt5Core)
BuildRequires:  pkgconfig(sailfishapp) >= 0.0.10

%description
JuveFood shows menus from any selected Juvenes restaurant.

- food names in Finnish or English (if translations are available)
- One or multiple restaurants can be selected


%prep
%setup -q -n %{name}-%{version}

# >> setup
# << setup

%build
# >> build pre
# << build pre

%qtc_qmake5  \
    VERSION='%{version}-%{release}'

%qtc_make %{?_smp_mflags}

# >> build post
# << build post

%install
rm -rf %{buildroot}
# >> install pre
# << install pre
%qmake5_install

# >> install post
# << install post

%files
%defattr(-,root,root,-)
/usr/bin
/usr/share/harbour-juvefood
/usr/share/applications
/usr/share/icons/hicolor/86x86/apps
# >> files
# << files
