module;
#include <imgui.h>
#include <implot.h>
export module widgets;
import std;
import texture;
export namespace widgets
{
    void centered_text(std::string_view text)
    {
        float text_width = ImGui::CalcTextSize(text.data()).x;
        float available_width = ImGui::GetContentRegionAvail().x;
        float indent_amount = (available_width - text_width) * 0.5f;
        ImGui::Indent(indent_amount);
        ImGui::Text("%s", text.data());
        ImGui::Unindent(indent_amount);
    }
    void centered_wrapped_text(std::string_view text)
    {
        float text_width = ImGui::CalcTextSize(text.data()).x;
        float available_width = ImGui::GetContentRegionAvail().x;
        if(text_width > available_width)
        {
            ImGui::TextWrapped("%s", text.data());
        }
        else
        {
            centered_text(text);
        }
    }
    void animated_waves(const float& time, ImVec2 window_size)
    {
        if (ImPlot::BeginPlot("Animated Waves", ImVec2(window_size.x * 0.8f, 0), ImPlotFlags_NoFrame | ImPlotFlags_NoInputs | ImPlotFlags_NoTitle | ImPlotAxisFlags_AutoFit))
        {
            static std::array<float, 100> x_data;
            static std::array<float, 100> y_sine;
            static std::array<float, 100> y_cosine;
            for (int i = 0; i < 100; ++i)
            {
                float x = i * 0.1f;
                x_data[i] = x;
                y_sine[i] = std::sin(x + time);   // Phase shift by time
                y_cosine[i] = std::cos(x + time); // Phase shift by time
            }
            ImPlot::SetupAxesLimits(x_data.front(), x_data.back(), -1.25, 1.25, ImPlotCond_Always);
            ImPlot::PlotLine("Sine", x_data.data(), y_sine.data(), 100);
            ImPlot::PlotLine("Cosine", x_data.data(), y_cosine.data(), 100);
            ImPlot::EndPlot();
        }
    }
    void gif(const float& time, ImVec2 window_size, std::vector<texture::image_data> gif_data)
    {
        int frame = static_cast<int>(time / (1.0F / 50.0f)) % gif_data.size();
        float aspect_ratio = static_cast<float>(gif_data[0].width) / static_cast<float>(gif_data[0].height);
        ImVec2 image_size = ImVec2(window_size.x * 0.8f, window_size.x * 0.8f / aspect_ratio);
        ImGui::Image((ImTextureID)(intptr_t)gif_data[frame].texture, image_size);
    }
    void centered_listbox(const char* label, int* selection, const std::vector<std::string>& items)
    {
        float max_text_width = 0.0f;
        for (const auto& item : items)
        {
            max_text_width = std::max(max_text_width, ImGui::CalcTextSize(item.c_str()).x);
        }
        std::vector<const char*> items_cstr;
        items_cstr.reserve(items.size());
        for (const auto& item : items)
        {
            items_cstr.push_back(item.c_str());
        }
        float available_width = ImGui::GetContentRegionAvail().x;
        float indent_amount = (available_width - max_text_width) * 0.5f;
        ImGui::SameLine(indent_amount - 10.0f);
        ImGui::SetNextItemWidth(max_text_width + 20.0f);
        ImGui::ListBox(label, selection, items_cstr.data(), items.size());
    }
}
