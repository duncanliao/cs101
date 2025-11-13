#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <set>
#include <cstdlib>

class LottoGenerator {
private:
    int groups;
    std::ofstream file;
    int issueNumber = 1;

    // 產生不重複的 7 個號碼
    std::vector<int> generateLotto() {
        std::set<int> nums;
        while (nums.size() < 7) {
            nums.insert(rand() % 69 + 1);
        }
        return std::vector<int>(nums.begin(), nums.end());
    }

    // 轉為兩位數字格式
    std::string fmt(int n) {
        std::ostringstream oss;
        oss << std::setw(2) << std::setfill('0') << n;
        return oss.str();
    }

    // 讀取上次期數
    void loadIssue() {
        std::ifstream fin("issue.txt");
        if (fin.is_open()) {
            fin >> issueNumber;
            fin.close();
        }
    }

    // 更新期數
    void saveIssue() {
        std::ofstream fout("issue.txt");
        fout << (issueNumber + 1);
        fout.close();
    }

public:
    LottoGenerator(int n) : groups(n) {
        srand(static_cast<unsigned int>(time(NULL)));
        loadIssue();
    }

    ~LottoGenerator() {
        if (file.is_open()) file.close();
        saveIssue();
    }

    void generate() {
        std::ostringstream filename;
        filename << "lotto" << std::setw(3) << std::setfill('0') << issueNumber << ".txt";
        file.open(filename.str());
        if (!file.is_open()) {
            std::cout << "無法建立檔案！\n";
            return;
        }

        file << "========= lotto649 =========\n";
        file << "========= No. " << std::setw(3) << std::setfill('0') << issueNumber <<" ========="<< "\n";

        time_t now = time(0);
        tm *ltm = localtime(&now);
        file << std::put_time(ltm, "%B %d %Y") << "\n";

        // 產生 5 組號碼
        for (int i = 1; i <= 5; ++i) {
            file << "[" << i << "]: ";
            if (i <= groups) {
                std::vector<int> nums = generateLotto();
                for (size_t j = 0; j < nums.size(); ++j) {
                    file << fmt(nums[j]);
                    if (j < 6) file << " ";
                }
            } else {
                file << "__ __ __ __ __ __ __";
            }
            file << "\n";
        }

        file << "========= csie@CGU =========\n";
        std::cout << "已產生 " << filename.str() << "！\n";
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
