// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// The original source code is from:
// http://src.chromium.org/viewvc/chrome/trunk/src/base/memory/scoped_ptr_unittest.cc?revision=79524

#include <libaddressinput/util/scoped_ptr.h>

#include <libaddressinput/util/basictypes.h>

#include <cstddef>

#include <gtest/gtest.h>

namespace {

using i18n::addressinput::scoped_ptr;

class ConDecLogger {
 public:
  ConDecLogger() : ptr_(NULL) { }
  explicit ConDecLogger(int* ptr) { set_ptr(ptr); }
  ~ConDecLogger() { --*ptr_; }

  void set_ptr(int* ptr) { ptr_ = ptr; ++*ptr_; }

  int SomeMeth(int x) { return x; }

 private:
  int* ptr_;
  DISALLOW_COPY_AND_ASSIGN(ConDecLogger);
};

TEST(ScopedPtrTest, ScopedPtr) {
  int constructed = 0;

  {
    scoped_ptr<ConDecLogger> scoper(new ConDecLogger(&constructed));
    EXPECT_EQ(1, constructed);
    EXPECT_TRUE(scoper.get());

    EXPECT_EQ(10, scoper->SomeMeth(10));
    EXPECT_EQ(10, scoper.get()->SomeMeth(10));
    EXPECT_EQ(10, (*scoper).SomeMeth(10));
  }
  EXPECT_EQ(0, constructed);

  // Test reset() and release()
  {
    scoped_ptr<ConDecLogger> scoper(new ConDecLogger(&constructed));
    EXPECT_EQ(1, constructed);
    EXPECT_TRUE(scoper.get());

    scoper.reset(new ConDecLogger(&constructed));
    EXPECT_EQ(1, constructed);
    EXPECT_TRUE(scoper.get());

    scoper.reset();
    EXPECT_EQ(0, constructed);
    EXPECT_FALSE(scoper.get());

    scoper.reset(new ConDecLogger(&constructed));
    EXPECT_EQ(1, constructed);
    EXPECT_TRUE(scoper.get());

    ConDecLogger* take = scoper.release();
    EXPECT_EQ(1, constructed);
    EXPECT_FALSE(scoper.get());
    delete take;
    EXPECT_EQ(0, constructed);

    scoper.reset(new ConDecLogger(&constructed));
    EXPECT_EQ(1, constructed);
    EXPECT_TRUE(scoper.get());
  }
  EXPECT_EQ(0, constructed);

  // Test swap(), == and !=
  {
    scoped_ptr<ConDecLogger> scoper1;
    scoped_ptr<ConDecLogger> scoper2;
    EXPECT_TRUE(scoper1 == scoper2.get());
    EXPECT_FALSE(scoper1 != scoper2.get());

    ConDecLogger* logger = new ConDecLogger(&constructed);
    scoper1.reset(logger);
    EXPECT_EQ(logger, scoper1.get());
    EXPECT_FALSE(scoper2.get());
    EXPECT_FALSE(scoper1 == scoper2.get());
    EXPECT_TRUE(scoper1 != scoper2.get());

    scoper2.swap(scoper1);
    EXPECT_EQ(logger, scoper2.get());
    EXPECT_FALSE(scoper1.get());
    EXPECT_FALSE(scoper1 == scoper2.get());
    EXPECT_TRUE(scoper1 != scoper2.get());
  }
  EXPECT_EQ(0, constructed);
}

}  // namespace
