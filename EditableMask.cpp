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

#include "EditableMask.hpp"
#include "ImageStack.hpp"
using namespace hdrmerge;


void EditableMask::startAction(bool add, int layer) {
    editActions.erase(nextAction, editActions.end());
    editActions.emplace_back();
    nextAction = editActions.end();
    editActions.back().oldLayer = add ? layer + 1 : layer;
    editActions.back().newLayer = add ? layer : layer + 1;
}


void EditableMask::editPixels(const ImageStack & images, int x, int y, size_t radius) {
    EditAction & e = editActions.back();
    mask.traceCircle(x, y, radius, [&] (int col, int row, uint8_t & layer) {
        if (layer == e.oldLayer && images.getImage(e.newLayer).contains(col, row)) {
            e.points.push_back({col, row});
            layer = e.newLayer;
        }
    });
}


EditableMask::Area EditableMask::undo() {
    Area result;
    if (nextAction != editActions.begin()) {
        --nextAction;
        result = modifyLayer(nextAction->points, nextAction->oldLayer);
    }
    return result;
}


EditableMask::Area EditableMask::redo() {
    Area result;
    if (nextAction != editActions.end()) {
        result = modifyLayer(nextAction->points, nextAction->newLayer);
        ++nextAction;
    }
    return result;
}


EditableMask::Area EditableMask::modifyLayer(const std::list<Point> & points, int layer) {
    Area a;
    a.minx = mask.getWidth() + 1;
    a.miny = mask.getHeight() + 1;
    a.maxx = -1;
    a.maxy = -1;
    for (auto p : points) {
        mask(p.x, p.y) = layer;
        if (p.x < a.minx) a.minx = p.x;
        if (p.x > a.maxx) a.maxx = p.x;
        if (p.y < a.miny) a.miny = p.y;
        if (p.y > a.maxy) a.maxy = p.y;
    }
    return a;
}