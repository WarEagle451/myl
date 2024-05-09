#include <myl_wip/ring_buffer.hpp>

#include <catch2/catch_all.hpp>

/// test cases: x = no element, o = element
/// xoox
/// xxoo
/// oxxo
/// ooxx
/// oooo
/// xxxx
/// 

TEST_CASE("myl::ring_buffer", "[ring_buffer.hpp]") {
    SECTION("constructor") {
        SECTION("default") {
            myl::ring_buffer<myl::i32> a;
            CHECK(a.size() == 0);
            CHECK(a.capacity() == 0);
            CHECK(a.offset() == 0);
            CHECK(a.linear());
            CHECK(a.empty());
            CHECK(a.full());
        }
        SECTION("copy") {
            SECTION("copy") {
                //myl::ring_buffer<myl::i32> a(3);
                //a.emplace_back(1);
                //a.emplace_back(2);
                //auto b = a;
                
                //CHECK(b.size() == 2);
                //CHECK(b.capacity() == 3);
                //CHECK(b.offset() == 0);
                //CHECK(b.linear());
                //CHECK(b.empty());
                //CHECK_FALSE(b.full());
                //CHECK(b == a);
            }
            SECTION("allocator") {

            }
        }
        SECTION("move") {
            SECTION("move") {

            }
            SECTION("allocator") {

            }
        }
        SECTION("allocator") {

        }
        SECTION("allocator") {

        }
        ///SECTION("elements") {
        ///    myl::ring_buffer<myl::i32> a;
        ///    CHECK(a.size() == 0);
        ///    CHECK(a.capacity() == 0);
        ///    CHECK(a.offset() == 0);
        ///    CHECK(a.linear());
        ///    CHECK(a.empty());
        ///    CHECK_FALSE(a.full());
        ///}
        SECTION("capacity") {
            myl::ring_buffer<myl::i32> a(10);
            CHECK(a.size() == 0);
            CHECK(a.capacity() == 10);
            CHECK(a.offset() == 0);
            CHECK(a.linear());
            CHECK(a.empty());
            CHECK_FALSE(a.full());
        }
        ///SECTION("count") {
        ///    myl::ring_buffer<myl::i32> a;
        ///    CHECK(a.size() == 0);
        ///    CHECK(a.capacity() == 0);
        ///    CHECK(a.offset() == 0);
        ///    CHECK(a.linear());
        ///    CHECK(a.empty());
        ///    CHECK_FALSE(a.full());
        ///}
        ///SECTION("iterator") {
        ///    myl::ring_buffer<myl::i32> a;
        ///    CHECK(a.size() == 0);
        ///    CHECK(a.capacity() == 0);
        ///    CHECK(a.offset() == 0);
        ///    CHECK(a.linear());
        ///    CHECK(a.empty());
        ///    CHECK_FALSE(a.full());
        ///}
    }
    SECTION("assignment") {
        SECTION("assignment") {

        }
        SECTION("assignment") {

        }
        SECTION("assignment") {

        }
    }
    SECTION("iterators") {
        SECTION("begin") {
            SECTION("begin") {

            }
            SECTION("begin - const") {

            }
        }
        SECTION("cbegin") {

        }
        SECTION("end") {
            SECTION("end") {

            }
            SECTION("end - const") {

            }
        }
        SECTION("cend") {

        }
        SECTION("rbegin") {
            SECTION("rbegin") {

            }
            SECTION("rbegin - const") {

            }
        }
        SECTION("crbegin") {

        }
        SECTION("rend") {
            SECTION("rend") {

            }
            SECTION("rend - const") {

            }
        }
        SECTION("crend") {

        }
    }
    SECTION("get_allocator") {

    }
    SECTION("data") {
        SECTION("data") {

        }
        SECTION("data - const") {

        }
    }
    SECTION("max_size") {

    }
    SECTION("size") {

    }
    SECTION("capacity") {

    }
    SECTION("offset") {

    }
    SECTION("linear") {

    }
    SECTION("empty") {

    }
    SECTION("full") {

    }
    SECTION("front") {
        SECTION("front") {

        }
        SECTION("front - const") {

        }
    }
    SECTION("back") {
        SECTION("back") {

        }
        SECTION("back - const") {

        }
    }
    SECTION("at") {
        SECTION("at") {

        }
        SECTION("at - const") {

        }
    }
    SECTION("operator[]") {
        SECTION("operator[]") {

        }
        SECTION("operator[] - const") {

        }
    }
    SECTION("clear") {

    }
    SECTION("fill") {

    }
    SECTION("saturate") {

    }
    SECTION("assign") {
        SECTION("iterator") {

        }
        SECTION("count") {

        }
        SECTION("elements") {

        }
    }
    SECTION("emplace_back") {
        myl::ring_buffer<myl::i32> a(3);
        a.emplace_back(1);
        a.emplace_back(2);

        CHECK(a.size() == 2);
        CHECK(a.capacity() == 3);
        CHECK(a.offset() == 0);
        CHECK(a.linear());
        CHECK_FALSE(a.empty());
        CHECK_FALSE(a.full());
        CHECK(a[0] == 1);
        CHECK(a[1] == 2);

        a.emplace_back(3);
        a.emplace_back(4);
        CHECK(a.size() == 3);
        CHECK(a.capacity() == 3);
        CHECK(a.offset() == 1);
        CHECK_FALSE(a.linear());
        CHECK_FALSE(a.empty());
        CHECK(a.full());
        CHECK(a[0] == 2);
        CHECK(a[1] == 3);
        CHECK(a[2] == 4);
    }
    SECTION("push_back") {
        SECTION("copy") {

        }
        SECTION("move") {

        }
    }
    SECTION("pop_back") {
        SECTION("pop_back") {
            myl::ring_buffer<myl::i32> a(2);
            a.push_back(1);
            a.push_back(2);

            a.pop_back();
            CHECK(a.size() == 1);
            CHECK(a.capacity() == 2);
            CHECK(a.offset() == 0);
            CHECK(a.linear());
            CHECK_FALSE(a.empty());
            CHECK_FALSE(a.full());
            CHECK(a.back() == 1);
        }
        SECTION("count") {
            myl::ring_buffer<myl::i32> a(3);
            a.push_back(1);
            a.push_back(2);
            a.push_back(3);

            a.pop_back(2);
            CHECK(a.size() == 1);
            CHECK(a.capacity() == 3);
            CHECK(a.offset() == 0);
            CHECK(a.linear());
            CHECK_FALSE(a.empty());
            CHECK_FALSE(a.full());
            CHECK(a.back() == 1);
        }
    }
    SECTION("emplace_front") {

    }
    SECTION("push_front") {
        SECTION("copy") {

        }
        SECTION("move") {

        }
    }
    SECTION("pop_front") {
        SECTION("pop_front") {
            myl::ring_buffer<myl::i32> a(2);
            a.push_back(1);
            a.push_back(2);

            a.pop_front();
            CHECK(a.size() == 1);
            CHECK(a.capacity() == 2);
            CHECK(a.offset() == 1);
            CHECK(a.linear());
            CHECK_FALSE(a.empty());
            CHECK_FALSE(a.full());
            CHECK(a.back() == 2);
        }
        SECTION("count") {
            myl::ring_buffer<myl::i32> a(3);
            a.push_back(1);
            a.push_back(2);
            a.push_back(3);

            a.pop_front(2);
            CHECK(a.size() == 1);
            CHECK(a.capacity() == 3);
            CHECK(a.offset() == 2);
            CHECK(a.linear());
            CHECK_FALSE(a.empty());
            CHECK_FALSE(a.full());
            CHECK(a.back() == 3);
        }
    }
    SECTION("resize") {

    }
    SECTION("reserve") {

    }
    SECTION("shrink_to_fit") {

    }
    SECTION("rotate") {
        SECTION("pointer") {

        }
        SECTION("offset") {

        }
    }
    SECTION("align") {

    }
    SECTION("comparision") {

    }
}
