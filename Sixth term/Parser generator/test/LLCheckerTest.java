import org.junit.Assert;
import org.junit.Test;

import java.util.*;

/**
 * @author Maxim Slyusarenko
 * @since 22.05.16
 */
public class LLCheckerTest {

    @Test
    public void testNotLLGrammar() {
        LLChecker checker = new LLChecker("!E");
        List<String> rule = new ArrayList<>();
        rule.add("!T");
        rule.add("+");
        rule.add("!E");
        checker.addRule("!E", rule);
        rule.clear();
        rule.add("!T");
        checker.addRule("!E", rule);
        rule.clear();
        rule.add("!F");
        rule.add("*");
        rule.add("!T");
        checker.addRule("!T", rule);
        rule.clear();
        rule.add("!F");
        checker.addRule("!T", rule);
        rule.clear();
        rule.add("n");
        checker.addRule("!F", rule);
        rule.clear();
        rule.add("(");
        rule.add("!E");
        rule.add(")");
        checker.addRule("!F", rule);
        Assert.assertFalse(checker.isLL());

        Set<String> expectedFirst = new HashSet<>();
        expectedFirst.add("n");
        expectedFirst.add("(");
        Map<String, Set<String>> first = checker.getFirst();
        for (Map.Entry<String, Set<String>> firstPart : first.entrySet()) {
            Assert.assertTrue(firstPart.getKey().equals("!E") || firstPart.getKey().equals("!T") || firstPart.getKey().equals("!F"));
            Assert.assertTrue(firstPart.getValue().equals(expectedFirst));
        }

        Set<String> expectedFollow = new HashSet<>();
        Map<String, Set<String>> follow = checker.getFollow();
        for (Map.Entry<String, Set<String>> followPart : follow.entrySet()) {
            if (followPart.getKey().equals("!E")) {
                expectedFollow.add(LLChecker.RULE_END);
                expectedFollow.add(")");
                Assert.assertTrue(followPart.getValue().equals(expectedFollow));
                expectedFollow.clear();
            } else if (followPart.getKey().equals("!T")) {
                expectedFollow.add(LLChecker.RULE_END);
                expectedFollow.add("+");
                expectedFollow.add(")");
                Assert.assertTrue(followPart.getValue().equals(expectedFollow));
                expectedFollow.clear();
            } else if (followPart.getKey().equals("!F")) {
                expectedFollow.add(LLChecker.RULE_END);
                expectedFollow.add("+");
                expectedFollow.add("*");
                expectedFollow.add(")");
                Assert.assertTrue(followPart.getValue().equals(expectedFollow));
                expectedFollow.clear();
            } else {
                Assert.assertTrue(false);
            }
        }
    }

    @Test
    public void testLLGrammar() {
        LLChecker checker = new LLChecker("!E");
        List<String> rule = new ArrayList<>();
        rule.add("!T");
        rule.add("!E'");
        checker.addRule("!E", rule);
        rule.clear();
        rule.add("+");
        rule.add("!T");
        rule.add("!E'");
        checker.addRule("!E'", rule);
        rule.clear();
        rule.add(LLChecker.EPSILON);
        checker.addRule("!E'", rule);
        rule.clear();
        rule.add("!F");
        rule.add("!T'");
        checker.addRule("!T", rule);
        rule.clear();
        rule.add("#"); // *, multiplication
        rule.add("!F");
        rule.add("!T'");
        checker.addRule("!T'", rule);
        rule.clear();
        rule.add(LLChecker.EPSILON);
        checker.addRule("!T'", rule);
        rule.clear();
        rule.add("n");
        checker.addRule("!F", rule);
        rule.clear();
        rule.add("(");
        rule.add("!E");
        rule.add(")");
        checker.addRule("!F", rule);
        checker.isLL();
        Assert.assertTrue(checker.isLL());

        Set<String> expectedFirst = new HashSet<>();
        Map<String, Set<String>> first = checker.getFirst();
        for (Map.Entry<String, Set<String>> firstPart : first.entrySet()) {
            if (firstPart.getKey().equals("!E")) {
                expectedFirst.add("n");
                expectedFirst.add("(");
                Assert.assertTrue(firstPart.getValue().equals(expectedFirst));
                expectedFirst.clear();
            } else if (firstPart.getKey().equals("!E'")) {
                expectedFirst.add("+");
                expectedFirst.add(LLChecker.EPSILON);
                Assert.assertTrue(firstPart.getValue().equals(expectedFirst));
                expectedFirst.clear();
            } else if (firstPart.getKey().equals("!T")) {
                expectedFirst.add("n");
                expectedFirst.add("(");
                Assert.assertTrue(firstPart.getValue().equals(expectedFirst));
                expectedFirst.clear();
            } else if (firstPart.getKey().equals("!T'")) {
                expectedFirst.add("#");
                expectedFirst.add(LLChecker.EPSILON);
                Assert.assertTrue(firstPart.getValue().equals(expectedFirst));
                expectedFirst.clear();
            } else if (firstPart.getKey().equals("!F")) {
                expectedFirst.add("n");
                expectedFirst.add("(");
                Assert.assertTrue(firstPart.getValue().equals(expectedFirst));
                expectedFirst.clear();
            } else {
                Assert.assertTrue(false);
            }
        }

        Set<String> expectedFollow = new HashSet<>();
        Map<String, Set<String>> follow = checker.getFollow();
        for (Map.Entry<String, Set<String>> followPart : follow.entrySet()) {
            if (followPart.getKey().equals("!E") || followPart.getKey().equals("!E'")) {
                expectedFollow.add(LLChecker.RULE_END);
                expectedFollow.add(")");
                Assert.assertTrue(followPart.getValue().equals(expectedFollow));
                expectedFollow.clear();
            } else if (followPart.getKey().equals("!T") || followPart.getKey().equals("!T'")) {
                expectedFollow.add(LLChecker.RULE_END);
                expectedFollow.add("+");
                expectedFollow.add(")");
                Assert.assertTrue(followPart.getValue().equals(expectedFollow));
                expectedFollow.clear();
            } else if (followPart.getKey().equals("!F")) {
                expectedFollow.add(LLChecker.RULE_END);
                expectedFollow.add("+");
                expectedFollow.add("#");
                expectedFollow.add(")");
                Assert.assertTrue(followPart.getValue().equals(expectedFollow));
                expectedFollow.clear();
            } else {
                Assert.assertTrue(false);
            }
        }
    }
}
