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
        ImGui::SetCursorPosX((ImGui::GetWindowWidth() - text_width) * 0.5f);
        ImGui::Text("%s", text.data());
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
}
