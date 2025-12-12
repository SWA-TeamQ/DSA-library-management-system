#include "Patron.hpp"
#include <iomanip>
#include <ctime>
using namespace std;

void Patron::displayProfile(ostream& os) const {
    time_t tt = chrono::system_clock::to_time_t(membershipDate);
    os << "PatronID: " << patronID << " | Name: " << name
       << " | Contact: " << contact << " | Since: " << put_time(localtime(&tt), "%Y-%m-%d")
       << '\n';
}
