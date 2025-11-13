#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <set>
#include <cstdlib>
#include <algorithm>

class LottoGenerator {
private:
    int groups;
    std::ofstream file;
    std::vector<std::vector<int>> tickets; // 儲存彩券

    // 產生一組不重複的 7 個數字 (1~69)
    std::vector<int> generateLotto() {
        std::set<int> selected;
        while (selected.size() < 7) {
            selected.insert(rand() % 69 + 1);
        }
        return std::vector<int>(selected.begin(), selected.end());
    }

    // 格式化數字為兩位數 (如 5 → "05")
    std::string formatNumber(int num) {
        std::ostringstream oss;
        oss << std::setw(2) << std::setfill('0') << num;
        return oss.str();
    }

    // 輸出到檔案與螢幕的統一函式
    void printLine(const std::string &line) {
        std::cout << line << "\n";
        file << line << "\n";
    }

public:
    LottoGenerator(int n) : groups(n) {
        srand(static_cast<unsigned int>(time(NULL))); // 每次執行不同亂數
    }

    bool openFile() {
        file.open("lotto.txt"); // 固定檔名
        return file.is_open();
    }

    void generate() {
        if (!openFile()) {
            std::cout << "無法開啟檔案！\n";
            return;
        }

        printLine("========= lotto649 =========");

        // 當前日期
        time_t now = time(0);
        tm *ltm = localtime(&now);
        std::ostringstream dateStream;
        dateStream << std::put_time(ltm, "%B %d %Y");
        printLine(dateStream.str());

        // 產生 5 組彩券
        for (int i = 1; i <= 5; ++i) {
            std::ostringstream line;
            line << "[" << i << "]: ";
            if (i <= groups) {
                std::vector<int> lotto = generateLotto();
                tickets.push_back(lotto);
                for (size_t j = 0; j < lotto.size(); ++j) {
                    line << formatNumber(lotto[j]);
                    if (j < 6) line << " ";
                }
            } else {
                line << "__ __ __ __ __ __ __";
            }
            printLine(line.str());
        }

        // 手動輸入中獎號碼
        std::vector<int> winNums;
        std::cout << "請輸入中獎號碼三個 (範圍 1~69，以空格分隔): ";
        for (int i = 0; i < 3; ++i) {
            int num;
            std::cin >> num;
            winNums.push_back(num);
        }

        std::ostringstream winLine;
        winLine << "輸入中獎號碼為: ";
        for (size_t i = 0; i < winNums.size(); ++i) {
            winLine << formatNumber(winNums[i]);
            if (i < winNums.size() - 1) winLine << " ";
        }
        printLine(winLine.str());

        // 判斷哪些彩券中獎
        printLine("以下為中獎彩券:");
        bool found = false;
        for (size_t i = 0; i < tickets.size(); ++i) {
            int matchCount = 0;
            for (int win : winNums) {
                if (std::find(tickets[i].begin(), tickets[i].end(), win) != tickets[i].end())
                    matchCount++;
            }

            if (matchCount >= 1) { // ✅ 只要中 1 個號碼就算中獎
                found = true;
                std::ostringstream line;
                line << "[" << (i + 1) << "]: ";
                for (size_t j = 0; j < tickets[i].size(); ++j) {
                    line << formatNumber(tickets[i][j]);
                    if (j < tickets[i].size() - 1) line << " ";
                }
                line << "  <-- 中 " << matchCount << " 個號碼";
                printLine(line.str());
            }
        }

        if (!found) {
            printLine("本期無中獎彩券。");
        }

        printLine("========= csie@CGU =========");

        std::cout << "lotto.txt 已成功產生，並完成對獎！\n";
    }
};

// ==================== main ====================
int main() {
    int n;
    std::cout << "請輸入要購買的組數 (1~5): ";
    std::cin >> n;

    LottoGenerator lotto(n);
    lotto.generate();

    return 0;
}
