#include "gtest/gtest.h"

#define TEST_TITLE "AAA"
#define TEST_TITLE_LEN 4
#define TEST_DURATION 234
#define TEST_BPM 90

extern "C" {
#include "composition.h"
}

class Composition_Tester {
private:
    char test_title[4];
    composition_t test_composition;

public:
    Composition_Tester();
    composition_t get_comp() {return test_composition;}
};

Composition_Tester::Composition_Tester() : test_title(TEST_TITLE) {
    test_composition.title.title = test_title;
    test_composition.title.len = TEST_TITLE_LEN;
    test_composition.duration = TEST_DURATION;
    test_composition.bpm = TEST_BPM;
}

Composition_Tester Tester;

TEST(CompositionTest, Create_OK) {
    composition_t filled_comp = Tester.get_comp();
    composition_t *comp = create_composition(filled_comp.title.title,
                                             filled_comp.title.len,
                                             filled_comp.duration,
                                             filled_comp.bpm);
    ASSERT_TRUE(comp);
    ASSERT_STREQ(filled_comp.title.title, comp->title.title);
    ASSERT_EQ(filled_comp.title.len, comp->title.len);
    ASSERT_EQ(filled_comp.duration, comp->duration);
    ASSERT_EQ(filled_comp.bpm, comp->bpm);
    delete_composition(comp);
}

TEST(CompositionTest, Create_Err) {
    composition_t filled_comp = Tester.get_comp();
    composition_t *comp = create_composition(NULL,
                                         filled_comp.title.len,
                                         filled_comp.duration,
                                         filled_comp.bpm);
    ASSERT_FALSE(comp);
}

TEST(CompositionTest, Delete) {
    ASSERT_EQ(delete_composition(NULL), -1);
    composition_t filled_comp = Tester.get_comp();
    composition_t *comp = create_composition(filled_comp.title.title,
                                             filled_comp.title.len,
                                             filled_comp.duration,
                                             filled_comp.bpm);
    ASSERT_EQ(delete_composition(comp), 0);
}

TEST(CompositionTest, Copy_OK) {
    composition_t filled_comp = Tester.get_comp();
    composition_t *comp = composition_cpy(&filled_comp);

    ASSERT_TRUE(comp);
    ASSERT_STREQ(filled_comp.title.title, comp->title.title);
    ASSERT_EQ(filled_comp.title.len, comp->title.len);
    ASSERT_EQ(filled_comp.duration, comp->duration);
    ASSERT_EQ(filled_comp.bpm, comp->bpm);
    delete_composition(comp);
}

TEST(CompositionTest, Copy_Err) {
    composition_t *comp = composition_cpy(NULL);
    ASSERT_FALSE(comp);
}

TEST(CompositionTest, Print) {
    composition_t comp = Tester.get_comp();
    ASSERT_EQ(print_composition(stdout, NULL), -1);
    ASSERT_EQ(print_composition(NULL, &comp), -1);
    ASSERT_EQ(print_composition(stdout, &comp), 0);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
