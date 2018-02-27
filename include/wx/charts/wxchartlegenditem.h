/*
    Copyright (c) 2018 Xavier Leclercq and the wxCharts contributors.

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
    IN THE SOFTWARE.
*/

/// @file

#ifndef _WX_CHARTS_WXCHARTLEGENDITEM_H_
#define _WX_CHARTS_WXCHARTLEGENDITEM_H_

#include <wx/vector.h>
#include <wx/colour.h>
#include <wx/string.h>

/// Class that represents items of the wxChartLegendData class.
class wxChartLegendItem
{
public:
    /// Constructs a wxChartLegendItem instance.
    /// @param color The color associated with this
    /// item on the chart.
    /// @param label The text to be display in the legend.
    wxChartLegendItem(const wxColor &color,
        const wxString &label);

    /// Gets the color of the item.
    /// @return The color of the item.
    const wxColor& GetColor() const;
    /// Gets the label of the item.
    /// @return The label of the item.
    const wxString& GetLabel() const;

private:
    wxColor m_color;
    wxString m_label;
};

typedef wxVector<wxChartLegendItem> wxChartLegendItems;

#endif
