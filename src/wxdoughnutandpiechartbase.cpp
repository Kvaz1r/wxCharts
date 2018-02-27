/*
    Copyright (c) 2016-2018 Xavier Leclercq and the wxCharts contributors.

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

/*
    Part of this file were copied from the Chart.js project (http://chartjs.org/)
    and translated into C++.

    The files of the Chart.js project have the following copyright and license.

    Copyright (c) 2013-2016 Nick Downie
    Released under the MIT license
    https://github.com/nnnick/Chart.js/blob/master/LICENSE.md
*/

#include "wxdoughnutandpiechartbase.h"

wxDoughnutAndPieChartBase::SliceArc::SliceArc(const wxChartSliceData &slice,
                                              wxDouble x,
                                              wxDouble y,
                                              wxDouble startAngle,
                                              wxDouble endAngle,
                                              wxDouble outerRadius,
                                              wxDouble innerRadius,
                                              unsigned int strokeWidth)
    : wxChartArc(x, y, startAngle, endAngle, outerRadius, innerRadius,
        slice.GetTooltipText(), wxChartArcOptions(strokeWidth, slice.GetColor())),
    m_value(slice.GetValue())
{
}

void wxDoughnutAndPieChartBase::SliceArc::Resize(const wxSize &size,
                                                 const wxDoughnutAndPieChartOptionsBase& options)
{
    wxDouble x = (size.GetX() / 2) - 2;
    wxDouble y = (size.GetY() / 2) - 2;
    wxDouble outerRadius = ((x < y) ? x : y) - (GetOptions().GetOutlineWidth() / 2);
    wxDouble innerRadius = outerRadius * ((wxDouble)options.GetPercentageInnerCutout()) / 100;

    SetCenter(x, y);
    SetRadiuses(outerRadius, innerRadius);
}

wxDouble wxDoughnutAndPieChartBase::SliceArc::GetValue() const
{
    return m_value;
}

void wxDoughnutAndPieChartBase::SliceArc::IncreaseValue(wxDouble val)
{
    m_value += val;
}

wxDoughnutAndPieChartBase::wxDoughnutAndPieChartBase()
    : m_total(0)
{
}

void wxDoughnutAndPieChartBase::Add(const wxChartSliceData &slice)
{
    m_total += slice.GetValue();
    auto key = slice.GetLabel();

    if(m_slices.find(key) == m_slices.end())
    {
        wxDouble x = (m_size.GetX() / 2) - 2;
        wxDouble y = (m_size.GetY() / 2) - 2;
        wxDouble outerRadius = ((x < y) ? x : y) - (GetOptions().GetSliceStrokeWidth() / 2);
        wxDouble innerRadius = outerRadius * ((wxDouble)GetOptions().GetPercentageInnerCutout()) / 100;

        SliceArc::ptr newSlice = SliceArc::ptr(new SliceArc(slice,
                                               x, y, 0, 0, outerRadius, innerRadius, GetOptions().GetSliceStrokeWidth()));
        m_slices[key] = newSlice;
    }
    else
        m_slices[key]->IncreaseValue(slice.GetValue());
}

void wxDoughnutAndPieChartBase::DoSetSize(const wxSize &size)
{
    m_size = size;
}

void wxDoughnutAndPieChartBase::DoFit()
{
    for (auto &slice : m_slices)
        slice.second->Resize(m_size, GetOptions());

    wxDouble startAngle = 0.0;
    for (auto &x : m_slices)
    {
        auto currentSlice = x.second;
        wxDouble endAngle = startAngle + CalculateCircumference(currentSlice->GetValue());
        currentSlice->SetAngles(startAngle, endAngle);
        startAngle = endAngle;
    }
}

void wxDoughnutAndPieChartBase::DoDraw(wxGraphicsContext &gc,
                                       bool suppressTooltips)
{
    Fit();

    for (auto &slice : m_slices)
        slice.second->Draw(gc);

    if (!suppressTooltips)
    {
        DrawTooltips(gc);
    }
}

wxSharedPtr<wxVector<const wxChartElement*> > wxDoughnutAndPieChartBase::GetActiveElements(const wxPoint &point)
{
    wxSharedPtr<wxVector<const wxChartElement*> > activeElements(new wxVector<const wxChartElement*>());
    for (auto &x : m_slices)
    {
        auto currentSlice = x.second;
        if (currentSlice->HitTest(point))
        {
            activeElements->push_back(currentSlice.get());
        }
    }
    return activeElements;
}

wxDouble wxDoughnutAndPieChartBase::CalculateCircumference(wxDouble value)
{
    if (m_total > 0)
    {
        return (value * 2 * M_PI / m_total);
    }
    else
    {
        return 0;
    }
}

void wxDoughnutAndPieChartBase::UpdateData(const wxVector<wxChartSliceData> &data)
{
    m_slices.clear();
    m_total = 0;
    for(const auto &slice : data)
        Add(slice);

    UpdateState();
}

void wxDoughnutAndPieChartBase::AddData(const wxVector<wxChartSliceData> &data)
{
    for(const auto &slice : data)
        Add(slice);
    UpdateState();
}

void wxDoughnutAndPieChartBase::UpdateState()
{
    wxChartLegendItems state;
    for(const auto &slice : m_slices)
        state.push_back(
            wxChartLegendItem(slice.second->GetOptions().GetFillColor(),slice.first));
    SetState(state);
}
