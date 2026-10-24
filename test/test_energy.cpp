/**
 * OpenWatt Node — native unit tests (PlatformIO Unity framework).
 * Run with: pio test -e native
 */
#include <unity.h>

// ── Logic under test (replicated; in prod share via lib/) ────────────────────

float simulatedWatts = 120.0f;
double cumulativeWh = 0.0;

void resetSimState() {
    simulatedWatts = 120.0f;
    cumulativeWh = 0.0;
}

/** Accumulate one second of energy at [watts]. Returns new cumulative Wh. */
double accumulateWh(double currentWh, float watts) {
    return currentWh + (double)watts / 3600.0;
}

/** Clamp watts reading to [0, ∞). */
float clampWatts(float watts) {
    return watts < 0.0f ? 0.0f : watts;
}

// ── Tests ────────────────────────────────────────────────────────────────────

void test_clamp_watts_no_negative() {
    TEST_ASSERT_EQUAL_FLOAT(0.0f, clampWatts(-50.0f));
}

void test_clamp_watts_positive_unchanged() {
    TEST_ASSERT_EQUAL_FLOAT(100.0f, clampWatts(100.0f));
}

void test_clamp_watts_zero_unchanged() {
    TEST_ASSERT_EQUAL_FLOAT(0.0f, clampWatts(0.0f));
}

void test_accumulate_wh_single_second_at_3600w() {
    // 3600 W for 1 second = 1.0 Wh
    double result = accumulateWh(0.0, 3600.0f);
    TEST_ASSERT_DOUBLE_WITHIN(0.0001, 1.0, result);
}

void test_accumulate_wh_zero_watts() {
    double result = accumulateWh(5.0, 0.0f);
    TEST_ASSERT_DOUBLE_WITHIN(0.0001, 5.0, result);
}

void test_accumulate_wh_120w_for_one_second() {
    // 120 W / 3600 = 0.0333 Wh per second
    double result = accumulateWh(0.0, 120.0f);
    TEST_ASSERT_DOUBLE_WITHIN(0.0001, 120.0 / 3600.0, result);
}

void test_accumulate_wh_is_cumulative() {
    double wh = 0.0;
    wh = accumulateWh(wh, 3600.0f); // 1.0 Wh
    wh = accumulateWh(wh, 3600.0f); // 2.0 Wh
    TEST_ASSERT_DOUBLE_WITHIN(0.0001, 2.0, wh);
}

void test_initial_simulated_watts() {
    resetSimState();
    TEST_ASSERT_EQUAL_FLOAT(120.0f, simulatedWatts);
}

void test_initial_cumulative_wh_zero() {
    resetSimState();
    TEST_ASSERT_DOUBLE_WITHIN(0.0001, 0.0, cumulativeWh);
}

void test_large_jitter_does_not_go_negative_after_clamp() {
    float w = 20.0f;
    w += -30.0f; // w = -10
    TEST_ASSERT_EQUAL_FLOAT(0.0f, clampWatts(w));
}

// ── Runner ───────────────────────────────────────────────────────────────────

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_clamp_watts_no_negative);
    RUN_TEST(test_clamp_watts_positive_unchanged);
    RUN_TEST(test_clamp_watts_zero_unchanged);
    RUN_TEST(test_accumulate_wh_single_second_at_3600w);
    RUN_TEST(test_accumulate_wh_zero_watts);
    RUN_TEST(test_accumulate_wh_120w_for_one_second);
    RUN_TEST(test_accumulate_wh_is_cumulative);
    RUN_TEST(test_initial_simulated_watts);
    RUN_TEST(test_initial_cumulative_wh_zero);
    RUN_TEST(test_large_jitter_does_not_go_negative_after_clamp);
    return UNITY_END();
}
