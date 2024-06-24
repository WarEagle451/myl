#include <myl_wip/static_vector.hpp>

#include <catch2/catch_all.hpp>

#include <array>

/// MYTODO: TEST Iterators

using element_type = myl::u8;

#define MYL_TEST_SV_CHECK(static_vector, size_, capacity_, empty_, full_)\
    CHECK(static_vector.size() == size_);\
    CHECK(static_vector.capacity() == capacity_);\
    CHECK(static_vector.empty() == empty_);\
    CHECK(static_vector.full() == full_);

TEST_CASE("myl::static_vector", "[static_vector.hpp]") {
    SECTION("constructor") {
        SECTION("default") {
            myl::static_vector<element_type, 4> sv;
            MYL_TEST_SV_CHECK(sv, 0, 4, true, false);
        }
        SECTION("copy") {
            myl::static_vector<element_type, 4> sv0{ 1, 2, 3 };
            myl::static_vector<element_type, 4> sv1(sv0);
            MYL_TEST_SV_CHECK(sv0, 3, 4, false, false);
            CHECK(sv0[0] == 1);
            CHECK(sv0[1] == 2);
            CHECK(sv0[2] == 3);
            MYL_TEST_SV_CHECK(sv1, 3, 4, false, false);
            CHECK(sv1[0] == 1);
            CHECK(sv1[1] == 2);
            CHECK(sv1[2] == 3);
        }
        SECTION("move") {
            myl::static_vector<element_type, 4> sv0{ 1, 2, 3 };
            myl::static_vector<element_type, 4> sv1(std::move(sv0));
            MYL_TEST_SV_CHECK(sv0, 3, 4, false, false);
            CHECK(sv1[0] == 1);
            CHECK(sv1[1] == 2);
            CHECK(sv1[2] == 3);
        }
        SECTION("count") {
            myl::static_vector<element_type, 4> sv(3, 5);
            MYL_TEST_SV_CHECK(sv, 3, 4, false, false);
            CHECK(sv[0] == 5);
            CHECK(sv[1] == 5);
            CHECK(sv[2] == 5);
        }
        SECTION("iterator") {
            std::array<element_type, 3> a{ 1, 2, 3 };
            myl::static_vector<element_type, 4> sv(a.begin(), a.end());
            MYL_TEST_SV_CHECK(sv, 3, 4, false, false);
            CHECK(sv[0] == 1);
            CHECK(sv[1] == 2);
            CHECK(sv[2] == 3);
        }
        SECTION("list") {
            myl::static_vector<element_type, 4> sv{ 1, 2, 3 };
            MYL_TEST_SV_CHECK(sv, 3, 4, false, false);
            CHECK(sv[0] == 1);
            CHECK(sv[1] == 2);
            CHECK(sv[2] == 3);
        }
        SECTION("copy of lesser size") {
            myl::static_vector<element_type, 3> sv0{ 1, 2 };
            myl::static_vector<element_type, 4> sv1(sv0);
            MYL_TEST_SV_CHECK(sv1, 2, 4, false, false);
            CHECK(sv1[0] == 1);
            CHECK(sv1[1] == 2);
        }
    }
    SECTION("assignment") {
        SECTION("copy") {
            myl::static_vector<element_type, 4> sv0{ 1, 2, 3 };
            myl::static_vector<element_type, 4> sv1{ 4, 5 };
            sv0 = sv1;
            MYL_TEST_SV_CHECK(sv0, 2, 4, false, false);
            CHECK(sv0[0] == 4);
            CHECK(sv0[1] == 5);
        }
        SECTION("move") {
            myl::static_vector<element_type, 4> sv0{ 1, 2, 3 };
            myl::static_vector<element_type, 4> sv1{ 4, 5 };
            sv0 = std::move(sv1);
            MYL_TEST_SV_CHECK(sv0, 2, 4, false, false);
            CHECK(sv0[0] == 4);
            CHECK(sv0[1] == 5);
        }
        SECTION("list") {
            myl::static_vector<element_type, 4> sv{ 1, 2, 3 };
            sv = { 4, 5, 6, 7 };
            MYL_TEST_SV_CHECK(sv, 4, 4, false, true);
            CHECK(sv[0] == 4);
            CHECK(sv[1] == 5);
            CHECK(sv[2] == 6);
            CHECK(sv[3] == 7);
        }
    }
    SECTION("max_size") {
        myl::static_vector<element_type, 4> sv0;
        myl::static_vector<element_type, 5> sv1;
    
        CHECK(sv0.max_size() == 4);
        CHECK(sv1.max_size() == 5);
    }
    SECTION("size") {
        myl::static_vector<element_type, 4> sv;
        CHECK(sv.size() == 0);
        sv.emplace_back(1);
        CHECK(sv.size() == 1);
        sv.emplace_back(2);
        CHECK(sv.size() == 2);
        sv.emplace_back(3);
        CHECK(sv.size() == 3);
        sv.emplace_back(4);
        CHECK(sv.size() == 4);
    }
    SECTION("capacity") {
        myl::static_vector<element_type, 4> sv;
        CHECK(sv.capacity() == 4);
    }
    SECTION("empty") {
        myl::static_vector<element_type, 4> sv;
        CHECK(sv.empty());
        sv.emplace_back(1);
        CHECK_FALSE(sv.empty());
    }
    SECTION("full") {
        myl::static_vector<element_type, 4> sv;
        CHECK_FALSE(sv.full());
        sv.fill(1);
        CHECK(sv.full());
    }
    SECTION("front") {
        SECTION("front") {
            myl::static_vector<element_type, 4> sv{ 1, 2, 3 };
            CHECK(sv.front() == 1);
        }
        SECTION("const") {
            const myl::static_vector<element_type, 4> sv{ 1, 2, 3 };
            CHECK(sv.front() == 1);
        }
    }
    SECTION("back") {
        SECTION("back") {
            myl::static_vector<element_type, 4> sv{ 1, 2, 3 };
            CHECK(sv.back() == 3);
        }
        SECTION("const") {
            const myl::static_vector<element_type, 4> sv{ 1, 2, 3 };
            CHECK(sv.back() == 3);
        }
    }
    SECTION("at") {
        SECTION("at") {
            myl::static_vector<element_type, 4> sv{ 1, 2, 3 };
            CHECK(sv.at(0) == 1);
            CHECK(sv.at(1) == 2);
            CHECK(sv.at(2) == 3);
        }
        SECTION("const") {
            const myl::static_vector<element_type, 4> sv{ 1, 2, 3 };
            CHECK(sv.at(0) == 1);
            CHECK(sv.at(1) == 2);
            CHECK(sv.at(2) == 3);
        }
    }
    SECTION("[]") {
        SECTION("[]") {
            myl::static_vector<element_type, 4> sv{ 1, 2, 3 };
            CHECK(sv[0] == 1);
            CHECK(sv[1] == 2);
            CHECK(sv[2] == 3);
        }
        SECTION("const") {
            const myl::static_vector<element_type, 4> sv{ 1, 2, 3 };
            CHECK(sv[0] == 1);
            CHECK(sv[1] == 2);
            CHECK(sv[2] == 3);
        }
    }
    SECTION("emplace") {
        myl::static_vector<element_type, 4> sv;
        sv.emplace(sv.end(), 1);
        sv.emplace(sv.begin(), element_type{ 2 });

        auto e0 = sv.begin() + 1;
        auto e1 = sv.emplace(e0, element_type{ 3 });
    
        MYL_TEST_SV_CHECK(sv, 3, 4, false, false);
        CHECK(sv[0] == 2);
        CHECK(sv[1] == 3);
        CHECK(sv[2] == 1);
        CHECK(e0 == e1);
    }
    SECTION("emplace_back") {
        myl::static_vector<element_type, 4> sv;
        sv.emplace_back(1);
        MYL_TEST_SV_CHECK(sv, 1, 4, false, false);
        CHECK(sv[0] == 1);
    
        sv.emplace_back(2);
        sv.emplace_back(3);
        auto& e = sv.emplace_back(4);
        MYL_TEST_SV_CHECK(sv, 4, 4, false, true);
        CHECK(sv[1] == 2);
        CHECK(sv[2] == 3);
        CHECK(sv[3] == 4);
        CHECK(e == 4);
    }
    SECTION("push_back") {
        SECTION("copy") {
            myl::static_vector<element_type, 4> sv;
            element_type a{ 1 };
            element_type b{ 2 };
            element_type c{ 3 };
            element_type d{ 4 };
    
            sv.push_back(a);
            MYL_TEST_SV_CHECK(sv, 1, 4, false, false);
            CHECK(sv[0] == 1);
    
            sv.push_back(b);
            sv.push_back(c);
            sv.push_back(d);
            MYL_TEST_SV_CHECK(sv, 4, 4, false, true);
            CHECK(sv[1] == 2);
            CHECK(sv[2] == 3);
            CHECK(sv[3] == 4);
        }
        SECTION("move") {
            myl::static_vector<element_type, 4> sv;
            element_type a{ 1 };
            element_type b{ 2 };
            element_type c{ 3 };
            element_type d{ 4 };
    
            sv.push_back(std::move(a));
            MYL_TEST_SV_CHECK(sv, 1, 4, false, false);
            CHECK(sv[0] == 1);
    
            sv.push_back(std::move(b));
            sv.push_back(std::move(c));
            sv.push_back(std::move(d));
            MYL_TEST_SV_CHECK(sv, 4, 4, false, true);
            CHECK(sv[1] == 2);
            CHECK(sv[2] == 3);
            CHECK(sv[3] == 4);
        }
    }
    SECTION("pop_back") {
        SECTION("single") {
            myl::static_vector<element_type, 4> sv{ 1, 2 };
            sv.pop_back();
            MYL_TEST_SV_CHECK(sv, 1, 4, false, false);
            CHECK(sv[0] == 1);
            sv.pop_back();
            MYL_TEST_SV_CHECK(sv, 0, 4, true, false);
        }
        SECTION("count") {
            myl::static_vector<element_type, 4> sv{ 1, 2, 3 };
            sv.pop_back(2);
            MYL_TEST_SV_CHECK(sv, 1, 4, false, false);
            CHECK(sv[0] == 1);
        }
    }
    SECTION("insert") {
        SECTION("copy") {
            myl::static_vector<element_type, 4> sv;
            element_type a{ 1 };
            element_type b{ 2 };
            element_type c{ 3 };
    
            sv.insert(sv.end(), a);
            sv.insert(sv.begin(), b);

            auto i0 = sv.begin() + 1;
            auto i1 = sv.insert(i0, c);

            MYL_TEST_SV_CHECK(sv, 3, 4, false, false);
            CHECK(sv[0] == 2);
            CHECK(sv[1] == 3);
            CHECK(sv[2] == 1);
            CHECK(i0 == i1);
        }
        SECTION("move") {
            myl::static_vector<element_type, 4> sv;
            element_type a{ 1 };
            element_type b{ 2 };
            element_type c{ 3 };
    
            sv.insert(sv.end(), std::move(a));
            sv.insert(sv.begin(), std::move(b));

            auto i0 = sv.begin() + 1;
            auto i1 = sv.insert(i0, std::move(c));

            MYL_TEST_SV_CHECK(sv, 3, 4, false, false);
            CHECK(sv[0] == 2);
            CHECK(sv[1] == 3);
            CHECK(sv[2] == 1);
            CHECK(i0 == i1);
        }
        SECTION("count") {
            
        }
        SECTION("iterator") {
    
        }
        SECTION("list") {
    
        }
    }
    SECTION("erase") {
        SECTION("single") {
            myl::static_vector<element_type, 4> sv{ 1, 2, 3 };
            auto i0 = sv.erase(sv.begin() + 1);
            MYL_TEST_SV_CHECK(sv, 2, 4, false, false);
            CHECK(sv[0] == 1);
            CHECK(sv[1] == 3);
            CHECK(*i0 == 3);
    
            auto i1 = sv.erase(sv.begin());
            MYL_TEST_SV_CHECK(sv, 1, 4, false, false);
            CHECK(sv[0] == 3);
            CHECK(*i1 == 3);
    
            auto i2 = sv.erase(sv.begin());
            MYL_TEST_SV_CHECK(sv, 0, 4, true, false);
            CHECK(i1 == sv.end());
        }
        SECTION("iterator") {
    
        }
    }
    SECTION("assign") {
        SECTION("count") {
            myl::static_vector<element_type, 4> sv;
            sv.assign(2, 5);
            MYL_TEST_SV_CHECK(sv, 2, 4, false, false);
            CHECK(sv[0] == 5);
            CHECK(sv[1] == 5);
        }
        SECTION("iterator") {
    
        }
        SECTION("list") {
    
        }
    }
    SECTION("clear") {
        myl::static_vector<element_type, 4> sv{ 1, 2, 3, 4 };
        MYL_TEST_SV_CHECK(sv, 4, 4, false, true);
        sv.clear();
        MYL_TEST_SV_CHECK(sv, 0, 4, true, false);
    }
    SECTION("fill") {
        myl::static_vector<element_type, 3> sv0;
        sv0.fill(2);
        MYL_TEST_SV_CHECK(sv0, 3, 3, false, true);
        CHECK(sv0[0] == 2);
        CHECK(sv0[1] == 2);
        CHECK(sv0[2] == 2);
    
        myl::static_vector<element_type, 3> sv1{ 1, 2, 3 };
        sv1.fill(4);
        MYL_TEST_SV_CHECK(sv1, 3, 3, false, true);
        CHECK(sv1[0] == 4);
        CHECK(sv1[1] == 4);
        CHECK(sv1[2] == 4);
    }
    SECTION("saturate") {
        myl::static_vector<element_type, 3> sv0;
        sv0.saturate(4);
        MYL_TEST_SV_CHECK(sv0, 3, 3, false, true);
        CHECK(sv0[0] == 4);
        CHECK(sv0[1] == 4);
        CHECK(sv0[2] == 4);
    
        myl::static_vector<element_type, 3> sv1{ 1, 2 };
        sv1.saturate(4);
        MYL_TEST_SV_CHECK(sv1, 3, 3, false, true);
        CHECK(sv1[0] == 1);
        CHECK(sv1[1] == 2);
        CHECK(sv1[2] == 4);
    
        myl::static_vector<element_type, 3> sv2{ 1, 2, 3 };
        sv2.saturate(4);
        MYL_TEST_SV_CHECK(sv2, 3, 3, false, true);
        CHECK(sv2[0] == 1);
        CHECK(sv2[1] == 2);
        CHECK(sv2[2] == 3);
    }
    SECTION("resize") {
        SECTION("count") {
    
        }
        SECTION("count of value") {
    
        }
    }
    SECTION("swap") {
    
    }
    SECTION("==") {
        myl::static_vector<element_type, 3> sv0;
        myl::static_vector<element_type, 3> sv1{ 1, 2 };
        myl::static_vector<element_type, 3> sv2{ 1, 2, 3 };
        myl::static_vector<element_type, 3> sv3{ 1, 2, 3 };
        myl::static_vector<element_type, 3> sv4{ 4, 5, 6 };
    
        CHECK(sv0 == sv0);
        CHECK_FALSE(sv0 == sv1);
        CHECK_FALSE(sv0 == sv2);
        CHECK_FALSE(sv0 == sv3);
        CHECK_FALSE(sv0 == sv4);
    
        CHECK_FALSE(sv1 == sv0);
        CHECK(sv1 == sv1);
        CHECK_FALSE(sv1 == sv2);
        CHECK_FALSE(sv1 == sv3);
        CHECK_FALSE(sv1 == sv4);
    
        CHECK_FALSE(sv2 == sv0);
        CHECK_FALSE(sv2 == sv1);
        CHECK(sv2 == sv2);
        CHECK(sv2 == sv3);
        CHECK_FALSE(sv2 == sv4);
    }
    SECTION("<=>") {
    
    }
    SECTION("std::swap") {
    
    }
    SECTION("std::erase") {
    
    }
    SECTION("std::erase_if") {
    
    }
}
