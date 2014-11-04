/* ***** BEGIN LICENSE BLOCK *****
 *
 *   Copyright (C) 2014, Peter Hatina <phatina@redhat.com>
 *
 *   This library is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU Lesser General Public License as
 *   published by the Free Software Foundation, either version 2.1 of the
 *   License, or (at your option) any later version.
 *
 *   This library is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU Lesser General Public License for more details.
 *
 *   You should have received a copy of the GNU Lesser General Public
 *   License along with this program; if not, write to the Free Software
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *   MA 02110-1301 USA
 *
 * ***** END LICENSE BLOCK ***** */

#  include <map>
#  include <string>
#  include <boost/python/to_python_converter.hpp>
#  include <Pegasus/Common/CIMType.h>
#  include "lmiwbem.h"
#  include "lmiwbem_constants.h"

BOOST_PYTHON_BEGIN
class object;
BOOST_PYTHON_END

PEGASUS_BEGIN
class Char16;
class CIMDateTime;
class CIMName;
class CIMObject;
class CIMObjectPath;
class CIMPropertyList;
class CIMValue;
class String;
PEGASUS_END

namespace bp = boost::python;

#ifndef   LMIWBEM_CONVERT_H
#  define LMIWBEM_CONVERT_H

#  define DECL_TO_CONVERTER(name, type) \
       struct name \
       { \
           static PyObject *convert(const type &val); \
           static void register_converter(); \
       }

#  define DEFINE_TO_CONVERTER(name, type) \
       void name::register_converter() \
       { \
           boost::python::to_python_converter<type, name>(); \
       } \
       PyObject *name::convert(const type &value)

DECL_TO_CONVERTER(PegasusStringToPythonString, Pegasus::String);
DECL_TO_CONVERTER(PegasusCIMNameToPythonString, Pegasus::CIMName);
DECL_TO_CONVERTER(PegasusCIMDateteTimeToPythonDateTime, Pegasus::CIMDateTime);
DECL_TO_CONVERTER(PegasusChar16ToPythonUint16, Pegasus::Char16);
DECL_TO_CONVERTER(PegasusCIMObjectPathToPythonCIMInstanceName, Pegasus::CIMObjectPath);
DECL_TO_CONVERTER(PegasusCIMObjectToPythonCIMObject, Pegasus::CIMObject);
DECL_TO_CONVERTER(CIMConstantsCIMErrorToPythonInt, CIMConstants::CIMError);

class CIMTypeConv
{
public:
    static std::string asStdString(Pegasus::CIMType type);
    static Pegasus::CIMType asCIMType(const std::string &type);

private:
    CIMTypeConv();

    class CIMTypeHolder
    {
    public:
        static CIMTypeHolder *instance();

        std::string get(Pegasus::CIMType type);
        Pegasus::CIMType get(const std::string &type);

    private:
        CIMTypeHolder();
        CIMTypeHolder(const CIMTypeHolder &copy) { }

        static boost::shared_ptr<CIMTypeHolder> s_instance;

        std::map<Pegasus::CIMType, std::string> m_type_string;
        std::map<std::string, Pegasus::CIMType> m_string_type;
    };

    static CIMTypeHolder s_type_holder;
};

class ListConv
{
public:
    static Pegasus::CIMPropertyList asPegasusPropertyList(
        const bp::object &property_list,
        const std::string &message);

private:
    ListConv();
};

class ObjectConv
{
public:
    static std::string asStdString(const bp::object &obj);
    static bp::object  asPyUnicode(const bp::object &obj);
};

class StringConv
{
public:
    static std::string asStdString(const bp::object &obj, bool &good);
    static std::string asStdString(const bp::object &obj);
    static bp::object  asPyUnicode(const char *str);
    static bp::object  asPyUnicode(const std::string &str);
    static bp::object  asPyUnicode(const Pegasus::String &str);
    static bp::object  asPyBool(const char *str);
    static bp::object  asPyBool(const std::string &str);
    static bp::object  asPyBool(const Pegasus::String &str);
#  if PY_MAJOR_VERSION < 3
    static bp::object  asPyInt(const char *str);
    static bp::object  asPyInt(const std::string &str);
    static bp::object  asPyInt(const Pegasus::String &str);
#  endif // PY_MAJOR_VERSION
    static bp::object  asPyFloat(const char *str);
    static bp::object  asPyFloat(const std::string &str);
    static bp::object  asPyFloat(const Pegasus::String &str);
    static bp::object  asPyLong(const char *str);
    static bp::object  asPyLong(const std::string &str);
    static bp::object  asPyLong(const Pegasus::String &str);

};

#endif // LMIWBEM_CONVERT_H