#include <myl/static_vector.hpp>

#include <catch2/catch_all.hpp>

#include <algorithm>

template<typename T>
auto static_vector_tests() -> void {
    SECTION("constructors") {
        SECTION("default") {
            myl::static_vector<T, 3> v;
            CHECK(v.size() == 0);
            CHECK(v.capacity() == 3);
            CHECK(v.empty() == true);
        }
        SECTION("copy") {
            myl::static_vector<T, 3> v1{ 1, 2, 3 };
            CHECK(v1.size() == 3);
            CHECK(v1.capacity() == 3);
            CHECK(v1.full() == true);

            myl::static_vector<T, 3> v2(v1);
            CHECK_FALSE("This is bugged");
            ///CHECK(std::equal(std::begin(v1), std::end(v1), std::begin(v2), std::end(v2)) == true);

            //
            
            myl::static_vector<T, 4> v3{ 1, 2, 3 };
            CHECK(v3.size() == 3);
            CHECK(v3.capacity() == 4);
            CHECK(v3.full() == true);

            myl::static_vector<T, 4> v4(v1);
            CHECK_FALSE("This is bugged");
            ///CHECK(std::equal(std::begin(v3), std::end(v3), std::begin(v4), std::end(v4)) == true);
        }
        SECTION("copy (of lesser capacity)") {

        }
        SECTION("move") {

        }
        SECTION("count (default initialized)") {

        }
        SECTION("count (value initialized)") {

        }
        SECTION("iterators") {

        }
        SECTION("list") {

        }
    }
    SECTION("assignment (copy)") {

    }
    SECTION("assignment (move)") {

    }
    SECTION("assignment (list)") {

    }
    SECTION("assign (count)") {

    }
    SECTION("assign (iterators)") {

    }
    SECTION("assign (list)") {

    }
    SECTION("at") {

    }
    SECTION("at (const)") {

    }
    SECTION("operator[]") {
        myl::static_vector<T, 3> v{ 1, 2, 3 };
        CHECK(v[0] == 1);
        CHECK(v[1] == 2);
        CHECK(v[2] == 3);
    }
    SECTION("operator[] (const)") {

    }
    SECTION("front") {
        myl::static_vector<T, 3> v1{ 1, 2, 3 };
        CHECK(v1.front() == 1);

        //

        myl::static_vector<T, 3> v2{ 1 };
        CHECK(v2.front() == 1);

    }
    SECTION("front (const)") {

    }
    SECTION("back") {
        myl::static_vector<T, 3> v1{ 1, 2, 3 };
        CHECK(v1.back() == 3);

        //

        myl::static_vector<T, 3> v2{ 1 };
        CHECK(v2.back() == 1);
    }
    SECTION("back (const)") {

    }
    SECTION("data") {

    }
    SECTION("data (const)") {

    }
    SECTION("empty") {
        myl::static_vector<T, 3> v1{ 1, 2, 3 };
        CHECK(v1.empty() == false);

        //

        myl::static_vector<T, 3> v2{ 1 };
        CHECK(v2.empty() == false);

        //

        myl::static_vector<T, 3> v3;
        CHECK(v3.empty() == true);
    }
    SECTION("full") {
        myl::static_vector<T, 3> v1{ 1, 2, 3 };
        CHECK(v1.full() == true);

        //

        myl::static_vector<T, 3> v2{ 1 };
        CHECK(v2.full() == false);

        //

        myl::static_vector<T, 3> v3;
        CHECK(v3.full() == false);
    }
    SECTION("size") {
        myl::static_vector<T, 3> v{ 1, 2 };
        CHECK(v.size() == 2);
    }
    SECTION("max_size") {
        myl::static_vector<T, 3> v{ 1 };
        CHECK(v.max_size() == 3);
    }
    SECTION("capacity") {
        myl::static_vector<T, 3> v{ 1 };
        CHECK(v.capacity() == 3);
    }
    SECTION("resize") {
        // Resize to max
        myl::static_vector<T, 3> v{};
        v.resize(3);
        CHECK(v.size() == 3);
        
        // Resize to 0
        v.resize(0);
        CHECK(v.size() == 0);
        
        // Resize with available capacity
        v.resize(2);
        CHECK(v.size() == 2);
       
        // Resize beyond capacity
///        v.resize(4);
///#ifndef MYL_NO_EXCEPTIONS
///        CHECK_THROWS(v.size() == 4);
///#else
///        CHECK(v.size() == 4);
///#endif
    }
    SECTION("resize (fill with value)") {

    }
    SECTION("insert (copy)") {

    }
    SECTION("insert (move)") {

    }
    SECTION("insert (count)") {

    }
    SECTION("insert (iterators)") {

    }
    SECTION("insert (list)") {

    }
    SECTION("emplace") {

    }
    SECTION("emplace_back") {

    }
    SECTION("try_emplace_back") {

    }
    SECTION("unchecked_emplace_back") {

    }
    SECTION("push_back (copy)") {

    }
    SECTION("push_back (move)") {

    }
    SECTION("try_push_back (copy)") {

    }
    SECTION("try_push_back (move)") {

    }
    SECTION("unchecked_emplace_back (copy)") {

    }
    SECTION("unchecked_emplace_back (move)") {

    }
    SECTION("pop_back") {

    }
    SECTION("pop_back (count)") {

    }
    SECTION("clear") {

    }
    SECTION("fill") {

    }
    SECTION("saturate") {

    }
    SECTION("erase") {

    }
    SECTION("erase (iterators)") {

    }
    SECTION("swap") {

    }
    SECTION("comparison") {
        SECTION("==") {

        }
        SECTION("!=") {

        }
        SECTION("<") {

        }
        SECTION("<=") {

        }
        SECTION(">") {

        }
        SECTION(">=") {

        }
    }
    SECTION("std::swap") {

    }
    SECTION("std::erase") {

    }
    SECTION("std::erase_if") {

    }
}

#include <myl_wip/unit_test.hpp>

TEST_CASE("myl::static_vector", "[static_vector.hpp]") {
    using test_element_type = myl::u8;

    MYL_TEST_CASE("test2");
    MYL_TEST_CASE("test2");

    //static_vector_tests<test_element_type>();
}

/// BELOW IS BAD
#if 0
#include <myl/static_vector.hpp>

#include <catch2/catch_all.hpp>

#include <array>

/// MYTODO: ENSURE THINGS THAT ARE SUPPOSE TO THROW DO THROW

#define MYL_TEST_SV_CHECK(static_vector, size_, capacity_, empty_, full_)\
    CHECK(static_vector.size() == size_);\
    CHECK(static_vector.capacity() == capacity_);\
    CHECK(static_vector.empty() == empty_);\
    CHECK(static_vector.full() == full_);

TEST_CASE("myl::static_vector", "[static_vector.hpp]") {
    SECTION("constructor") {
        SECTION("move") {
            myl::static_vector<element_type, 4> sv0{ 1, 2, 3 };
            myl::static_vector<element_type, 4> sv1(std::move(sv0));

            MYL_TEST_SV_CHECK(sv1, 3, 4, false, false);
            CHECK(sv1[0] == 1);
            CHECK(sv1[1] == 2);
            CHECK(sv1[2] == 3);
        }
        SECTION("count") {
            element_type a{ 5 };
            myl::static_vector<element_type, 4> sv(3, a);

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
            std::initializer_list<element_type> l{ 1, 2, 3 };
            myl::static_vector<element_type, 4> sv(l);

            MYL_TEST_SV_CHECK(sv, 3, 4, false, false);
            CHECK(sv[0] == 1);
            CHECK(sv[1] == 2);
            CHECK(sv[2] == 3);
        }
        SECTION("copy of lesser capacity") {
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
            
            MYL_TEST_SV_CHECK(sv1, 2, 4, false, false);
            CHECK(sv1[0] == 4);
            CHECK(sv1[1] == 5);
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
            std::initializer_list<element_type> l{ 4, 5, 6, 7 };
            myl::static_vector<element_type, 4> sv{ 1, 2, 3 };

            sv = l;

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
        element_type a{ 1 };

        CHECK(sv.size() == 0);

        sv.emplace_back(a);
        CHECK(sv.size() == 1);

        sv.emplace_back(a);
        CHECK(sv.size() == 2);

        sv.emplace_back(a);
        CHECK(sv.size() == 3);

        sv.emplace_back(a);
        CHECK(sv.size() == 4);
    }
    SECTION("capacity") {
        myl::static_vector<element_type, 4> sv;
        CHECK(sv.capacity() == 4);
    }
    SECTION("empty") {
        myl::static_vector<element_type, 4> sv;
        element_type a{ 1 };

        CHECK(sv.empty());

        sv.emplace_back(a);
        CHECK_FALSE(sv.empty());
    }
    SECTION("full") {
        myl::static_vector<element_type, 4> sv;
        element_type a{ 1 };

        CHECK_FALSE(sv.full());

        sv.fill(a);

        CHECK(sv.full());
    }
    SECTION("front") {
        SECTION("front") {
            myl::static_vector<element_type, 4> sv{ 1, 2, 3 };
            element_type a{ 1 };

            CHECK(sv.front() == a);
        }
        SECTION("const") {
            const myl::static_vector<element_type, 4> sv{ 1, 2, 3 };
            element_type a{ 1 };

            CHECK(sv.front() == a);
        }
    }
    SECTION("back") {
        SECTION("back") {
            myl::static_vector<element_type, 4> sv{ 1, 2, 3 };
            element_type a{ 3 };

            CHECK(sv.back() == a);
        }
        SECTION("const") {
            const myl::static_vector<element_type, 4> sv{ 1, 2, 3 };
            element_type a{ 3 };

            CHECK(sv.back() == a);
        }
    }
    SECTION("at") {
        SECTION("at") {
            element_type a{ 1 };
            element_type b{ 2 };
            element_type c{ 3 };
            myl::static_vector<element_type, 4> sv{ a, b, c };

            CHECK(sv.at(0) == a);
            CHECK(sv.at(1) == b);
            CHECK(sv.at(2) == c);
        }
        SECTION("const") {
            const element_type a{ 1 };
            const element_type b{ 2 };
            const element_type c{ 3 };
            const myl::static_vector<element_type, 4> sv{ a, b, c };

            CHECK(sv.at(0) == a);
            CHECK(sv.at(1) == b);
            CHECK(sv.at(2) == c);
        }
    }
    SECTION("[]") {
        SECTION("[]") {
            element_type a{ 1 };
            element_type b{ 2 };
            element_type c{ 3 };
            myl::static_vector<element_type, 4> sv{ a, b, c };

            CHECK(sv[0] == a);
            CHECK(sv[1] == b);
            CHECK(sv[2] == c);
        }
        SECTION("const") {
            const element_type a{ 1 };
            const element_type b{ 2 };
            const element_type c{ 3 };
            const myl::static_vector<element_type, 4> sv{ a, b, c };

            CHECK(sv[0] == a);
            CHECK(sv[1] == b);
            CHECK(sv[2] == c);
        }
    }
    SECTION("emplace") {
        myl::static_vector<element_type, 4> sv;
        element_type a{ 1 };
        element_type b{ 2 };

        sv.emplace(sv.end(), a);
        sv.emplace(sv.begin(), std::move(b));

        auto e0 = sv.begin() + 1;
        auto e1 = sv.emplace(e0, 3);
    
        MYL_TEST_SV_CHECK(sv, 3, 4, false, false);
        CHECK(sv[0] == 2);
        CHECK(sv[1] == 3);
        CHECK(sv[2] == a);
        CHECK(e0 == e1);
    }
    SECTION("emplace_back") {
        myl::static_vector<element_type, 4> sv;
        element_type a{ 1 };
        element_type b{ 2 };
        element_type c{ 3 };

        sv.emplace_back(a);

        MYL_TEST_SV_CHECK(sv, 1, 4, false, false);
        CHECK(sv[0] == 1);
    
        sv.emplace_back(b);
        sv.emplace_back(std::move(c));
        auto& e = sv.emplace_back(4);

        MYL_TEST_SV_CHECK(sv, 4, 4, false, true);
        CHECK(sv[1] == b);
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
            CHECK(sv[0] == a);
    
            sv.push_back(b);
            sv.push_back(c);
            sv.push_back(d);

            MYL_TEST_SV_CHECK(sv, 4, 4, false, true);
            CHECK(sv[1] == b);
            CHECK(sv[2] == c);
            CHECK(sv[3] == d);
        }
        SECTION("move") {
            myl::static_vector<element_type, 4> sv;
            element_type a{ 1 };
            element_type b{ 2 };
            element_type c{ 3 };
            element_type d{ 4 };
    
            sv.push_back(std::move(a));

            MYL_TEST_SV_CHECK(sv, 1, 4, false, false);
            CHECK(sv[0] == a);
    
            sv.push_back(std::move(b));
            sv.push_back(std::move(c));
            sv.push_back(std::move(d));

            MYL_TEST_SV_CHECK(sv, 4, 4, false, true);
            CHECK(sv[1] == b);
            CHECK(sv[2] == c);
            CHECK(sv[3] == d);
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
            myl::static_vector<element_type, 4> sv;

            sv.insert(sv.end(), 2, 1);
            MYL_TEST_SV_CHECK(sv, 2, 4, false, false);
            CHECK(sv[0] == 1);
            CHECK(sv[1] == 1);

            sv.insert(sv.begin() + 1, 2, 2);
            MYL_TEST_SV_CHECK(sv, 4, 4, false, true);
            CHECK(sv[0] == 1);
            CHECK(sv[1] == 2);
            CHECK(sv[2] == 2);
            CHECK(sv[3] == 1);
        }
        SECTION("iterator") {
            std::array<element_type, 2> a{ 1, 2 };
            myl::static_vector<element_type, 4> sv;

            sv.insert(sv.end(), a.begin(), a.end());
            MYL_TEST_SV_CHECK(sv, 2, 4, false, false);
            CHECK(sv[0] == 1);
            CHECK(sv[1] == 2);

            sv.insert(sv.begin(), a.rbegin(), a.rend());
            MYL_TEST_SV_CHECK(sv, 4, 4, false, true);
            CHECK(sv[0] == 2);
            CHECK(sv[1] == 1);
            CHECK(sv[2] == 1);
            CHECK(sv[3] == 2);
        }
        SECTION("list") {
            myl::static_vector<element_type, 4> sv;

            sv.insert(sv.end(), { 1, 2 });
            MYL_TEST_SV_CHECK(sv, 2, 4, false, false);
            CHECK(sv[0] == 1);
            CHECK(sv[1] == 2);

            sv.insert(sv.begin() + 1, { 3, 4 });
            MYL_TEST_SV_CHECK(sv, 4, 4, false, true);
            CHECK(sv[0] == 1);
            CHECK(sv[1] == 3);
            CHECK(sv[2] == 4);
            CHECK(sv[3] == 2);
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
            CHECK(i2 == sv.end());
        }
        SECTION("iterator") {
            myl::static_vector<element_type, 4> sv{ 1, 2, 3, 4 };
            auto i0 = sv.erase(sv.begin() + 1, sv.end() - 1);
            MYL_TEST_SV_CHECK(sv, 2, 4, false, false);
            CHECK(sv[0] == 1);
            CHECK(sv[1] == 4);
            CHECK(*i0 == 4);

            auto i1 = sv.erase(sv.begin(), sv.end());
            MYL_TEST_SV_CHECK(sv, 0, 4, true, false);
            CHECK(i1 == sv.end());
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
            std::array<element_type, 3> a{ 1, 2, 3 };
            myl::static_vector<element_type, 4> sv;
            sv.assign(a.begin(), a.end());
            MYL_TEST_SV_CHECK(sv, 3, 4, false, false);
            CHECK(sv[0] == 1);
            CHECK(sv[1] == 2);
            CHECK(sv[2] == 3);
        }
        SECTION("list") {
            myl::static_vector<element_type, 4> sv;
            sv.assign({ 1, 2, 3 });
            MYL_TEST_SV_CHECK(sv, 3, 4, false, false);
            CHECK(sv[0] == 1);
            CHECK(sv[1] == 2);
            CHECK(sv[2] == 3);
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
            myl::static_vector<element_type, 4> sv{ 1, 2 };
            sv.resize(3);
            MYL_TEST_SV_CHECK(sv, 3, 4, false, false);
            CHECK(sv[0] == 1);
            CHECK(sv[1] == 2);
            CHECK(sv[2] == element_type{});

            sv.resize(1);
            MYL_TEST_SV_CHECK(sv, 1, 4, false, false);
            CHECK(sv[0] == 1);
        }
        SECTION("count of value") {
            myl::static_vector<element_type, 4> sv{ 1, 2 };
            sv.resize(3, element_type{ 5 });
            MYL_TEST_SV_CHECK(sv, 3, 4, false, false);
            CHECK(sv[0] == 1);
            CHECK(sv[1] == 2);
            CHECK(sv[2] == element_type{ 5 });

            sv.resize(1, element_type{ 5 });
            MYL_TEST_SV_CHECK(sv, 1, 4, false, false);
            CHECK(sv[0] == 1);
        }
    }
    SECTION("swap") {
        myl::static_vector<element_type, 4> sv0{ 1, 2, 3 };
        myl::static_vector<element_type, 4> sv1{ 4, 5 };
        myl::static_vector<element_type, 4> sv2{ 6, 7, 8, 9 };
        myl::static_vector<element_type, 4> sv3;
        myl::static_vector<element_type, 4> sv4{ 10, 11, 12, 13 };
        sv0.swap(sv1);

        MYL_TEST_SV_CHECK(sv0, 2, 4, false, false);
        CHECK(sv0[0] == 4);
        CHECK(sv0[1] == 5);

        MYL_TEST_SV_CHECK(sv1, 3, 4, false, false);
        CHECK(sv1[0] == 1);
        CHECK(sv1[1] == 2);
        CHECK(sv1[2] == 3);

        sv2.swap(sv3);

        MYL_TEST_SV_CHECK(sv2, 0, 4, true, false);
        MYL_TEST_SV_CHECK(sv3, 4, 4, false, true);
        CHECK(sv3[0] == 6);
        CHECK(sv3[1] == 7);
        CHECK(sv3[2] == 8);
        CHECK(sv3[3] == 9);

        sv4.swap(sv3);

        MYL_TEST_SV_CHECK(sv3, 4, 4, false, true);
        CHECK(sv3[0] == 10);
        CHECK(sv3[1] == 11);
        CHECK(sv3[2] == 12);
        CHECK(sv3[3] == 13);

        MYL_TEST_SV_CHECK(sv4, 4, 4, false, true);
        CHECK(sv4[0] == 6);
        CHECK(sv4[1] == 7);
        CHECK(sv4[2] == 8);
        CHECK(sv4[3] == 9);
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
        myl::static_vector<element_type, 4> sv0{ 1, 2, 4 };
        myl::static_vector<element_type, 4> sv1{ 1, 3 };
        myl::static_vector<element_type, 4> sv2{ 2, 1 };

        CHECK_FALSE(sv0 < sv0);
        CHECK(sv0 <= sv0);
        CHECK_FALSE(sv0 > sv0);
        CHECK(sv0 >= sv0);

        CHECK(sv0 < sv1);
        CHECK(sv0 <= sv1);
        CHECK_FALSE(sv0 > sv1);
        CHECK_FALSE(sv0 >= sv1);

        CHECK_FALSE(sv2 < sv1);
        CHECK_FALSE(sv2 <= sv1);
        CHECK(sv2 > sv1);
        CHECK(sv2 >= sv1);
    }
    SECTION("std::swap") {
        myl::static_vector<element_type, 4> sv0{ 1, 2, 3 };
        myl::static_vector<element_type, 4> sv1{ 4, 5 };
        std::swap(sv1, sv0);

        MYL_TEST_SV_CHECK(sv0, 2, 4, false, false);
        CHECK(sv0[0] == 4);
        CHECK(sv0[1] == 5);

        MYL_TEST_SV_CHECK(sv1, 3, 4, false, false);
        CHECK(sv1[0] == 1);
        CHECK(sv1[1] == 2);
        CHECK(sv1[2] == 3);
    }
    SECTION("std::erase") {
        myl::static_vector<element_type, 5> sv{ 1, 2, 1, 3, 1 };
        auto erased = std::erase(sv, 1);
        
        MYL_TEST_SV_CHECK(sv, 2, 5, false, false);
        CHECK(sv[0] == 2);
        CHECK(sv[1] == 3);
        CHECK(erased == 3);
    }
    SECTION("std::erase_if") {
        myl::static_vector<element_type, 5> sv{ 4, 2, 1, 3, 6 };
        auto erased = std::erase_if(sv, [](element_type x) { return x > 2; });

        MYL_TEST_SV_CHECK(sv, 2, 5, false, false);
        CHECK(sv[0] == 2);
        CHECK(sv[1] == 1);
        CHECK(erased == 3);
    }
}
#endif