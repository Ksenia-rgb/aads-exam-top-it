#include "sol.hpp"
#include <iostream>
#include <fstream>

namespace petrov
{
  template<class T>
  void grow_vec(T* data, size_t& c, size_t& s)
  {
    size_t new_c = c * 2;
    T* new_d = new T[new_c];
    for (size_t i = 0; i < s; ++i)
    {
      new_d[i] = data[i];
    }
    delete[] data;
    data = new_d;
    c = new_c;
  }

  size_t cycle(int argc, char** argv)
  {
    if (argc < 2 || argc > 3)
    {
      std::cerr << "too much\n";
      return 1;
    }
    std::string inf = "", df = "";
    for (int i = 1; i < argc; ++i) {
      std::string arg = argv[i];
      if (!arg.rfind("in:", 0)) {
        if (!inf.empty()) {
          std::cerr << "dubl\n";
          return 1;
        }
        inf = arg.substr(3);
      } else if (!arg.rfind("data:", 0)) {
        if (!df.empty()) {
          std::cerr << "dubl\n";
          return 1;
        }
        df = arg.substr(5);
      } else {
        std::cerr << "inval\n";
        return 1;
      }
    }
    if (df.empty())
    {
      std::cerr << "err\n";
      return 1;
    }
    Pvec ps = {nullptr, 0, 0};
    Mvec ms = {nullptr, 0, 0};

    if (!inf.empty())
    {
      std::ifstream fin(inf.c_str());
      if (!fin)
      {
        std::cerr << "err\n";
        delete[] ps.dat;
        delete[] ms.dat;
        return 2;
      }
      std::string l = "";
      while (std::getline(fin, l))
      {
        size_t id = 0;
        while (id < l.size() && (l[id] == ' ' || l[id] == '\t')) {
          id = id + 1;
        }
        if (id == l.size()) {
          continue;
        }
        if (l[id] < '0' || l[id] > '9') {
          continue;
        }
        size_t num = 0;
        while (id < l.size() && l[id] >= '0' && l[id] <= '9') {
          num = num * 10 + static_cast<size_t>(l[id] - '0');
          id = id + 1;
        }
        while (id < l.size() && (l[id] == ' ' || l[id] == '\t')) {
          id = id + 1;
        }
        if (id == l.size()) {
          continue;
        }
        std::string txt = l.substr(id);
        bool dup = 0;
        for (size_t i = 0; i < ps.s; ++i) {
          if (ps.dat[i].id == num) {
            dup = 1;
            break;
          }
        }
        if (dup) {
          continue;
        }
        if (ps.s == ps.c) {
          size_t nc = ps.c * 2;
          if (nc == 0) {
            nc = 2;
          }
          Person* nd = new Person[nc];
          for (size_t i = 0; i < ps.s; ++i) {
            nd[i] = ps.dat[i];
          }
          delete[] ps.dat;
          ps.dat = nd;
          ps.c = nc;
        }
        ps.dat[ps.s].id = num;
        ps.dat[ps.s].info = txt;
        ps.dat[ps.s].h_i = 1;
        ps.dat[ps.s].del = 0;
        ps.s = ps.s + 1;
      }
    }

    std::ifstream f_dt(df.c_str());
    if (!f_dt) {
      std::cerr << "open err\n";
      delete[] ps.dat;
      delete[] ms.dat;
      return 2;
    }
    size_t id1 = 0;
    size_t id2 = 0;
    size_t len = 0;
    while (f_dt >> id1 >> id2 >> len) {
      if (id1 == id2) {
        continue;
      }
      bool f1 = 0;
      bool f2 = 0;
      for (size_t i = 0; i < ps.s; ++i) {
        if (ps.dat[i].id == id1) {
          f1 = 1;
        }
        if (ps.dat[i].id == id2) {
          f2 = 1;
        }
      }
      if (!f1) {
        if (ps.s == ps.c) {
          size_t nc = ps.c * 2;
          if (nc == 0) {
            nc = 2;
          }
          Person* nd = new Person[nc];
          for (size_t i = 0; i < ps.s; ++i) {
            nd[i] = ps.dat[i];
          }
          delete[] ps.dat;
          ps.dat = nd;
          ps.c = nc;
        }
        ps.dat[ps.s].id = id1;
        ps.dat[ps.s].info = "";
        ps.dat[ps.s].h_i = 0;
        ps.dat[ps.s].del = 0;
        ps.s = ps.s + 1;
      }
      if (!f2) {
        if (ps.s == ps.c) {
          size_t nc = ps.c * 2;
          if (nc == 0) {
            nc = 2;
          }
          Person* nd = new Person[nc];
          for (size_t i = 0; i < ps.s; ++i) {
            nd[i] = ps.dat[i];
          }
          delete[] ps.dat;
          ps.dat = nd;
          ps.c = nc;
        }
        ps.dat[ps.s].id = id2;
        ps.dat[ps.s].info = "";
        ps.dat[ps.s].h_i = 0;
        ps.dat[ps.s].del = 0;
        ps.s = ps.s + 1;
      }
      if (ms.s == ms.c) {
        size_t nc = ms.c * 2;
        if (nc == 0) {
          nc = 2;
        }
        Meeting* nd = new Meeting[nc];
        for (size_t i = 0; i < ms.s; ++i) {
          nd[i] = ms.dat[i];
        }
        delete[] ms.dat;
        ms.dat = nd;
        ms.c = nc;
      }
      ms.dat[ms.s].i1 = id1;
      ms.dat[ms.s].i2 = id2;
      ms.dat[ms.s].t = len;
      ms.dat[ms.s].del = 0;
      ms.s = ms.s + 1;
    }
    if (f_dt.fail() && !f_dt.eof()) {
      std::cerr << "read err\n";
      delete[] ps.dat;
      delete[] ms.dat;
      return 3;
    }
    std::string cmd = "";
    while (std::cin >> cmd) {
      if (cmd == "anons") {
        size_t ac = 0;
        for (size_t i = 0; i < ps.s; ++i) {
          if (ps.dat[i].del == 0 && ps.dat[i].h_i == 0) {
            ac = ac + 1;
          }
        }
        if (ac > 0) {
          size_t* arr = new size_t[ac];
          size_t cur = 0;
          for (size_t i = 0; i < ps.s; ++i) {
            if (ps.dat[i].del == 0 && ps.dat[i].h_i == 0) {
              arr[cur] = ps.dat[i].id;
              cur = cur + 1;
            }
          }
          for (size_t i = 0; i < ac; ++i) {
            for (size_t j = i + 1; j < ac; ++j) {
              if (arr[i] > arr[j]) {
                size_t tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
              }
            }
          }
          for (size_t i = 0; i < ac; ++i) {
            std::cout << arr[i] << "\n";
          }
          delete[] arr;
        }
      } else if (cmd == "deanon") {
        size_t an_id = 0;
        size_t r_id = 0;
        if (!(std::cin >> an_id >> r_id)) {
          std::cin.clear();
          std::string dummy = "";
          std::cin >> dummy;
          std::cout << "<INVALID COMMAND>\n";
          continue;
        }
        int p_an = -1;
        int p_r = -1;
        for (size_t i = 0; i < ps.s; ++i) {
          if (ps.dat[i].del == 0 && ps.dat[i].id == an_id) {
            p_an = static_cast<int>(i);
          }
          if (ps.dat[i].del == 0 && ps.dat[i].id == r_id) {
            p_r = static_cast<int>(i);
          }
        }
        if (p_an == -1 || p_r == -1 || ps.dat[p_an].h_i != 0 || ps.dat[p_r].h_i == 0) {
          std::cout << "<INVALID COMMAND>\n";
          continue;
        }
        ps.dat[p_an].del = 1;
        for (size_t i = 0; i < ms.s; ++i) {
          if (ms.dat[i].del == 0) {
            if (ms.dat[i].i1 == an_id) {
              ms.dat[i].i1 = r_id;
            }
            if (ms.dat[i].i2 == an_id) {
              ms.dat[i].i2 = r_id;
            }
            if (ms.dat[i].i1 == ms.dat[i].i2) {
              ms.dat[i].del = 1;
            }
          }
        }
      } else if (cmd == "redesc") {
        size_t r_id = 0;
        if (!(std::cin >> r_id)) {
          std::cin.clear();
          std::string dummy = "";
          std::cin >> dummy;
          std::cout << "<INVALID COMMAND>\n";
          continue;
        }
        char ch = 0;
        while (std::cin.get(ch)) {
          if (ch != ' ' && ch != '\t' && ch != '\n') {
            break;
          }
        }
        if (ch != '"') {
          std::cout << "<INVALID COMMAND>\n";
          continue;
        }
        std::string desc_str = "";
        bool ok = 0;
        while (std::cin.get(ch)) {
          if (ch == '"') {
            ok = 1;
            break;
          }
          desc_str = desc_str + ch;
        }
        if (!ok) {
          std::cout << "<INVALID COMMAND>\n";
          continue;
        }
        int p_idx = -1;
        for (size_t i = 0; i < ps.s; ++i) {
          if (ps.dat[i].del == 0 && ps.dat[i].id == r_id) {
            p_idx = static_cast<int>(i);
          }
        }
        if (p_idx == -1) {
          std::cout << "<INVALID COMMAND>\n";
          continue;
        }
        ps.dat[p_idx].info = desc_str;
        ps.dat[p_idx].h_i = 1;
      } else if (cmd == "desc") {
        size_t r_id = 0;
        if (!(std::cin >> r_id)) {
          std::cin.clear();
          std::string dummy = "";
          std::cin >> dummy;
          std::cout << "<INVALID COMMAND>\n";
          continue;
        }
        int p_idx = -1;
        for (size_t i = 0; i < ps.s; ++i) {
          if (ps.dat[i].del == 0 && ps.dat[i].id == r_id) {
            p_idx = static_cast<int>(i);
          }
        }
        if (p_idx == -1) {
          std::cout << "<INVALID COMMAND>\n";
          continue;
        }
        if (ps.dat[p_idx].h_i == 0) {
          std::cout << "<ANON>\n";
        } else {
          std::cout << ps.dat[p_idx].info << "\n";
        }
      } else if (cmd == "meets" || cmd == "less" || cmd == "greater") {
        size_t limit = 0;
        if (cmd == "less" || cmd == "greater") {
          if (!(std::cin >> limit)) {
            std::cin.clear();
            std::string dummy = "";
            std::cin >> dummy;
            std::cout << "<INVALID COMMAND>\n";
            continue;
          }
        }
        size_t r_id = 0;
        if (!(std::cin >> r_id)) {
          std::cin.clear();
          std::string dummy = "";
          std::cin >> dummy;
          std::cout << "<INVALID COMMAND>\n";
          continue;
        }
                bool ex = 0;
        for (size_t i = 0; i < ps.s; ++i) {
          if (ps.dat[i].del == 0 && ps.dat[i].id == r_id) {
            ex = 1;
          }
        }
        if (!ex) {
          std::cout << "<INVALID COMMAND>\n";
          continue;
        }
        size_t mc = 0;
        for (size_t i = 0; i < ms.s; ++i) {
          if (ms.dat[i].del == 0) {
            if (ms.dat[i].i1 == r_id || ms.dat[i].i2 == r_id) {
              if (cmd == "meets" || (cmd == "less" && ms.dat[i].t < limit) || (cmd == "greater" && ms.dat[i].t > limit)) {
                mc = mc + 1;
              }
            }
          }
        }
        if (mc > 0) {
          std::pair<size_t, size_t>* arr = new std::pair<size_t, size_t>[mc];
          size_t cur = 0;
          for (size_t i = 0; i < ms.s; ++i) {
            if (ms.dat[i].del == 0) {
              if (ms.dat[i].i1 == r_id || ms.dat[i].i2 == r_id) {
                if (cmd == "meets" || (cmd == "less" && ms.dat[i].t < limit) || (cmd == "greater" && ms.dat[i].t > limit)) {
                  size_t oth = ms.dat[i].i1;
                  if (ms.dat[i].i1 == r_id) {
                    oth = ms.dat[i].i2;
                  }
                  arr[cur] = std::make_pair(oth, ms.dat[i].t);
                  cur = cur + 1;
                }
              }
            }
          }
          for (size_t i = 0; i < mc; ++i) {
            for (size_t j = i + 1; j < mc; ++j) {
              bool swp = 0;
              if (arr[i].first > arr[j].first) {
                swp = 1;
              } else if (arr[i].first == arr[j].first) {
                if (arr[i].second > arr[j].second) {
                  swp = 1;
                }
              }
              if (swp) {
                std::pair<size_t, size_t> tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
              }
            }
          }
          for (size_t i = 0; i < mc; ++i) {
            std::cout << arr[i].first << " " << arr[i].second << "\n";
          }
          delete[] arr;
        }
      } else if (cmd == "commons") {
        size_t id_a = 0;
        size_t id_b = 0;
        if (!(std::cin >> id_a >> id_b)) {
          std::cin.clear();
          std::string dummy = "";
          std::cin >> dummy;
          std::cout << "<INVALID COMMAND>\n";
          continue;
        }
        bool ex_a = 0;
        bool ex_b = 0;
        for (size_t i = 0; i < ps.s; ++i) {
          if (ps.dat[i].del == 0) {
            if (ps.dat[i].id == id_a) {
              ex_a = 1;
            }
            if (ps.dat[i].id == id_b) {
              ex_b = 1;
            }
          }
        }
        if (!ex_a || !ex_b) {
          std::cout << "<INVALID COMMAND>\n";
          continue;
        }
        size_t cc = 0;
        for (size_t i = 0; i < ps.s; ++i) {
          if (ps.dat[i].del == 0) {
            size_t cid = ps.dat[i].id;
            bool m_a = 0;
            bool m_b = 0;
            for (size_t j = 0; j < ms.s; ++j) {
              if (ms.dat[j].del == 0) {
                if ((ms.dat[j].i1 == id_a && ms.dat[j].i2 == cid) || (ms.dat[j].i2 == id_a && ms.dat[j].i1 == cid)) {
                  m_a = 1;
                }
                if ((ms.dat[j].i1 == id_b && ms.dat[j].i2 == cid) || (ms.dat[j].i2 == id_b && ms.dat[j].i1 == cid)) {
                  m_b = 1;
                }
              }
            }
            if (m_a && m_b) {
              cc = cc + 1;
            }
          }
        }
        if (cc > 0) {
          size_t* arr = new size_t[cc];
          size_t cur = 0;
          for (size_t i = 0; i < ps.s; ++i) {
            if (ps.dat[i].del == 0) {
              size_t cid = ps.dat[i].id;
              bool m_a = false;
              bool m_b = false;
              for (size_t j = 0; j < ms.s; ++j) {
                if (ms.dat[j].del == 0) {
                  if ((ms.dat[j].i1 == id_a && ms.dat[j].i2 == cid) || (ms.dat[j].i2 == id_a && ms.dat[j].i1 == cid)) {
                    m_a = true;
                  }
                  if ((ms.dat[j].i1 == id_b && ms.dat[j].i2 == cid) || (ms.dat[j].i2 == id_b && ms.dat[j].i1 == cid)) {
                    m_b = true;
                  }
                }
              }
              if (m_a && m_b) {
                arr[cur] = cid;
                cur = cur + 1;
              }
            }
          }
          for (size_t i = 0; i < cc; ++i) {
            for (size_t j = i + 1; j < cc; ++j) {
              if (arr[i] > arr[j]) {
                size_t tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
              }
            }
          }
          for (size_t i = 0; i < cc; ++i) {
            std::cout << arr[i] << "\n";
          }
          delete[] arr;
        }
      } else if (cmd == "out-persons") {
        std::string path = "";
        if (!(std::cin >> path)) {
          std::cin.clear();
          std::string dummy = "";
          std::cin >> dummy;
          std::cout << "<INVALID COMMAND>\n";
          continue;
        }
        std::ofstream f_out(path.c_str());
        if (!f_out) {
          std::cout << "<INVALID COMMAND>\n";
          continue;
        }
        for (size_t i = 0; i < ps.s; ++i) {
          if (ps.dat[i].del == 0 && ps.dat[i].h_i == 1) {
            f_out << ps.dat[i].id << " " << ps.dat[i].info << "\n";
          }
        }
      } else {
        std::cout << "<INVALID COMMAND>\n";
      }
    }

    delete[] ps.dat;
    delete[] ms.dat;
    return 0;
  }
}
