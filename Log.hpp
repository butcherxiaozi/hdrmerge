/*
 *  HDRMerge - HDR exposure merging software.
 *  Copyright 2012 Javier Celaya
 *  jcelaya@gmail.com
 *
 *  This file is part of HDRMerge.
 *
 *  HDRMerge is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  HDRMerge is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with HDRMerge. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef _LOG_HPP_
#define _LOG_HPP_

#include <ostream>
#include <string>
#include <QString>

namespace hdrmerge {

class Log {
public:
    enum {
        DEBUG = 0,
        PROGRESS = 1,
    } Priority;

    template <typename... Args>
    static void msg(int priority, const Args &... params) {
        Log & l = getInstance();
        if (l.out && priority >= l.minPriority) {
            l.output(params...);
            *l.out << std::endl;
        }
    }

    static void setMinimumPriority(int p) {
        getInstance().minPriority = p;
    }

    static void setOutputStream(std::ostream & o) {
        getInstance().out = &o;
    }

private:
    int minPriority;
    std::ostream * out;

    Log() : minPriority(2), out(nullptr) {}

    static Log & getInstance() {
        static Log instance;
        return instance;
    }

    void output() {}

    template<typename T, typename... Args>
    void output(const T & value, const Args &... args) {
        *out << value;
        output(args...);
    }
};


inline std::ostream & operator<<(std::ostream & os, const QString & s) {
    return os << std::string(s.toUtf8().constData());
}

} // namespace hdrmerge

#endif // _LOG_HPP_
