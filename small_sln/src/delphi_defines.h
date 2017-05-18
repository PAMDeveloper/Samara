/*
    This file is part of delphi2cpp, written by Ivan Vecerina, (C) 2003-2007.

    delphi2cpp is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    delphi2cpp is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with delphi2cpp.  If not, see <http://www.gnu.org/licenses/>.
*/
#pragma once

#include <set>
#include <map>
#include <string>
#include <sstream>
#include <algorithm>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#include <cmath>
#include <iostream>
#include "DateTime.hpp"

//#define Q(x) #x
//#define AfficheMessageErreur(A, B) std::cout << A << Q(x);

#define AfficheMessageErreur(A, B)  ;
#define try  ;
#define catch(x)  ;

static double NilValue = -999;
static double sqr(double x) {return x * x;}

static double DayOfTheYear(double date) {
  return artis::utils::DateTime::dayOfYear(date);
}

static std::string FloatToStr(double val) {
  return std::to_string(val);
}


