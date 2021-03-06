/* Goxel 3D voxels editor
 *
 * copyright (c) 2017 Guillaume Chereau <guillaume@noctua-software.com>
 *
 * Goxel is free software: you can redistribute it and/or modify it under the
 * terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.

 * Goxel is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.

 * You should have received a copy of the GNU General Public License along with
 * goxel.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "goxel.h"

static int iter(int state, void **data,
                const vec4_t *view, bool inside)
{
    cursor_t *curs = &goxel->cursor;
    curs->snap_mask = SNAP_MESH;
    curs->snap_offset = 0;

    goxel_set_help_text(goxel, "Click on the mesh to set plane.");

    if (curs->snaped && (curs->flags & CURSOR_PRESSED)) {
        curs->pos.x = round(curs->pos.x);
        curs->pos.y = round(curs->pos.y);
        curs->pos.z = round(curs->pos.z);
        goxel->plane = plane_from_normal(curs->pos, curs->normal);
    }
    return 0;
}

static int gui(void)
{
    int i;
    gui_group_begin(NULL);
    i = 0;
    if (gui_input_int("Move", &i, 0, 0))
        mat4_itranslate(&goxel->plane.mat, 0, 0, -i);
    i = 0;
    if (gui_input_int("Rot X", &i, 0, 0))
        mat4_irotate(&goxel->plane.mat, i * M_PI / 2, 1, 0, 0);
    i = 0;
    if (gui_input_int("Rot Y", &i, 0, 0))
        mat4_irotate(&goxel->plane.mat, i * M_PI / 2, 0, 1, 0);
    gui_group_end();
    return 0;
}

TOOL_REGISTER(TOOL_SET_PLANE, plane,
              .iter_fn = iter,
              .gui_fn = gui,
              .shortcut = "P"
)
