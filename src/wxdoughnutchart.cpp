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

#include "wxdoughnutchart.h"

wxDoughnutChartData::wxDoughnutChartData()
{
}

void wxDoughnutChartData::AppendSlice(const wxChartSliceData &slice)
{
    m_slices.push_back(slice);
}

const wxVector<wxChartSliceData>& wxDoughnutChartData::GetSlices() const
{
    return m_slices;
}

wxDoughnutChart::wxDoughnutChart(const wxDoughnutChartData &data,
                                 const wxSize &size)
{
    Initialize(data, size);
}

wxDoughnutChart::wxDoughnutChart(const wxDoughnutChartData &data,
                                 const wxDougnutChartOptions &options,
                                 const wxSize &size)
    : m_options(options)
{
    Initialize(data, size);
}

const wxDougnutChartOptions& wxDoughnutChart::GetOptions() const
{
    return m_options;
}

void wxDoughnutChart::Initialize(const wxDoughnutChartData &data,
                                 const wxSize &size)
{
    AddData(data.GetSlices());
}
