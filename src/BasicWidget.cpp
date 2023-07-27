#include "BasicWidget.h"

#include <array>
#include <mutex>
#include <string>
#include <vector>

#include "ApplicationState.h"
#include "FakeData.h"
#include "Utils.h"
#include "imgui.h"

namespace op {

static void menuBarWidget() {
    if (ImGui::BeginMenuBar()) {
        if (ImGui::BeginMenu("Hihi")) {
            ImGui::MenuItem("Test", nullptr, false);
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Examples")) {
            ImGui::MenuItem("Test", nullptr, true);
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }
}

template <bool isCall>
static void callOrPutTable(TableStateByExpiry& tableData) {
    static constexpr std::string tableName = isCall ? "Calls" : "Puts";

    // Prepare the data
    std::vector<float>& strikes = tableData.strikes;
    std::vector<TableRowData>* rowsPtr;
    if constexpr (isCall) {
        rowsPtr = &tableData.callRowData;
    } else {
        rowsPtr = &tableData.putRowData;
    }
    std::vector<TableRowData>& rows = *rowsPtr;

    static ImGuiTableFlags flags =
        ImGuiTableFlags_Resizable | ImGuiTableFlags_Hideable | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV;
    if (ImGui::BeginTable(tableName.c_str(), op::TABLE_COLUMN_NAMES.size(), flags)) {
        // Submit columns name with TableSetupColumn() and call TableHeadersRow() to create a row with a header in each
        // column.
        for (const char* header : op::TABLE_COLUMN_NAMES) {
            ImGui::TableSetupColumn(header);
        }

        ImGui::TableHeadersRow();
        for (std::size_t row = 0; row < strikes.size(); ++row) {
            TableRowData& data = rows[row];
            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::Text("%.2f", data.lastTradedPrice);
            ImGui::TableSetColumnIndex(1);
            ImGui::Text("%.2f", data.bidSize);
            ImGui::TableSetColumnIndex(2);
            ImGui::Text("%.2f", data.bidVol);
            ImGui::TableSetColumnIndex(3);
            ImGui::Text("%.2f", data.bidPrice);
            ImGui::TableSetColumnIndex(4);
            ImGui::Text("%.2f", data.askPrice);
            ImGui::TableSetColumnIndex(5);
            ImGui::Text("%.2f", data.askVol);
            ImGui::TableSetColumnIndex(6);
            ImGui::Text("%.2f", data.askSize);
            ImGui::TableSetColumnIndex(7);
            ImGui::Text("%.2f", data.openInterest);
            ImGui::TableSetColumnIndex(8);
            ImGui::Text("%.2f", data.delta);
            ImGui::TableSetColumnIndex(9);
            ImGui::Text("%.2f", data.gamma);
            ImGui::TableSetColumnIndex(10);
            ImGui::Text("%.2f", data.vega);
            ImGui::TableSetColumnIndex(11);
            ImGui::Text("%.2f", data.theta);
            ImGui::TableSetColumnIndex(12);
            ImGui::Text("%.2f", data.rho);
            ImGui::TableSetColumnIndex(13);
            ImGui::Text("%.2f", data.volume);
            ImGui::TableSetColumnIndex(14);
            ImGui::Text("%.2f", data.position);
        }
        ImGui::EndTable();
    }
}

static void strikesTable(TableStateByExpiry& tableData) {
    std::vector<float>& strikes = tableData.strikes;

    static ImGuiTableFlags flags = ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV;
    if (ImGui::BeginTable("strikes table", 1, flags)) {
        ImGui::TableSetupColumn("Strike");
        ImGui::TableHeadersRow();
        for (std::size_t row = 0; row < strikes.size(); ++row) {
            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::Text("%.2f", strikes[row]);
        }
        ImGui::EndTable();
    }
}

static void mainTable(TableStateByExpiry& tableData) {
    if (ImGui::BeginTable("table_nested1", 3,
                          ImGuiTableFlags_Borders | ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable |
                              ImGuiTableFlags_Hideable)) {
        ImGui::TableSetupColumn("Calls");
        ImGui::TableSetupColumn("---");
        ImGui::TableSetupColumn("Puts");
        ImGui::TableHeadersRow();

        ImGui::TableNextColumn();
        callOrPutTable<true>(tableData);

        ImGui::TableNextColumn();
        strikesTable(tableData);

        ImGui::TableNextColumn();
        callOrPutTable<false>(tableData);

        ImGui::EndTable();
    }
}

static void expirationTabs() {
    const std::vector<const char*> expirationDates = {"26 JUL 23", "27 JUL 23", "28 JUL 23", "04 AUG 23",
                                                      "11 AUG 23", "25 AUG 23", "29 SEP 23", "29 DEC 23"};
    ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
    if (ImGui::BeginTabBar("MyTabBar", tab_bar_flags)) {
        for (const char* expiryStr : expirationDates) {
            if (ImGui::BeginTabItem(expiryStr)) {
                ImGui::Text("Expiry: %s", expiryStr);
                ImGui::EndTabItem();
            }
        }
        ImGui::EndTabBar();
    }
}

void renderBasicWidget(ApplicationState& appState, ImGuiIO& io) {
    static float f = 0.0f;
    static int counter = 0;

    // Get table data
    {
        std::lock_guard<std::mutex> lock(appState.wrappedTableData.mutex);
        if (appState.wrappedTableData.processed) {
            // auto tableDataFuture = std::async(std::launch::async, fake::getFakeDataForTable);
            auto tableDataFuture = op::reallyAsync(fake::getFakeDataForTable);
            if (tableDataFuture.wait_for(std::chrono::milliseconds(100)) == std::future_status::ready) {
                appState.wrappedTableData.tsbe = tableDataFuture.get();
                appState.wrappedTableData.processed = true;
            } else {
                appState.wrappedTableData.processed = false;
            }
        }
    }

    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar;
    // ImGui::Begin("My ImGui", nullptr, window_flags);
    if (!ImGui::Begin("My ImGui", nullptr, window_flags)) {
        // Early out if the window is collapsed, as an optimization.
        ImGui::End();
        return;
    }

    menuBarWidget();
    expirationTabs();
    mainTable(appState.wrappedTableData.tsbe);

    ImGui::Text("This is some useful text.");  // Display some text (you can use a format strings too)
    ImGui::Checkbox("Demo Window",
                    &appState.show_demo_window);  // Edit bools storing our window open/close state
    ImGui::SameLine();
    ImGui::Checkbox("Another Window", &appState.show_another_window);

    ImGui::Checkbox("Enable power saver",
                    &appState.enable_power_save);  // Edit bools storing our window open/close state

    ImGui::SliderFloat("float", &f, 0.0f, 1.0f);                      // Edit 1 float using a slider from 0.0f to 1.0f
    ImGui::ColorEdit3("clear color", (float*)&appState.clear_color);  // Edit 3 floats representing a color

    if (ImGui::Button("Button"))  // Buttons return true when clicked (most widgets return true when edited/activated)
        counter++;
    ImGui::SameLine();
    ImGui::Text("counter = %d", counter);

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
    ImGui::End();
}

}  // namespace op
