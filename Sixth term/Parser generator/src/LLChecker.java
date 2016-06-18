import javafx.util.Pair;

import java.util.*;

/**
 * @author Maxim Slyusarenko
 * @since 20.05.15
 */
public class LLChecker {

    public static final String EPSILON = "EPSILON";
    public static final String RULE_END = "END";

    private final String start;
    private final Map<String, List<List<String>>> rules;
    private final Map<String, List<Pair<List<String>, Map<String, List<String>>>>> rulesWithActions;
    private Map<String, Set<String>> first;
    private Map<String, Set<String>> follow;
    private final Map<String, Set<String>> allRegexps;
    private final Map<String, String> givenRegexps;
    private final Set<String> skipRules;
    private final Map<String, String> tokens;
    private final Map<String, String> initBlocks;
    private final Map<String, Set<String>> parametersNamesForUnterm;
    private final Map<String, Set<String>> returnsNamesForUnterm;
    private final Map<String, Set<String>> localsNamesForUnterm;

    public LLChecker(String start) {
        this.start = start;
        rules = new HashMap<>();
        rulesWithActions = new HashMap<>();
        allRegexps = new HashMap<>();
        givenRegexps = new HashMap<>();
        skipRules = new HashSet<>();
        tokens = new TreeMap<>();
        initBlocks = new HashMap<>();
        parametersNamesForUnterm = new HashMap<>();
        returnsNamesForUnterm = new HashMap<>();
        localsNamesForUnterm = new HashMap<>();
    }

    public void add(String left, List<String> right, Map<String, List<List<String>>> where) {
        if (where.containsKey(left)) {
            where.get(left).add(new ArrayList<>(right));
        } else {
            List<List<String>> current = new ArrayList<>();
            current.add(new ArrayList<>(right));
            where.put(left, current);
        }
        String currentToken = "";
        for (String rulePart : right) {
            if (rulePart.startsWith("!") || rulePart.startsWith("*")) {
                if (!tokens.containsValue(currentToken) && !currentToken.isEmpty()) {
                    tokens.put("TOKEN_" + tokens.size(), currentToken);
                }
                currentToken = "";
            } else if (rulePart.startsWith("~")) {
                continue;
            } else {
                currentToken += rulePart;
            }
        }
        if (!tokens.containsValue(currentToken) && !currentToken.isEmpty()) {
            tokens.put("TOKEN_" + tokens.size(), currentToken);
        }
    }

    public void addRule(String left, List<String> right) {
        add(left, right, rules);
    }

    public void addRuleWithActions(String left, List<String> right, Map<String, List<String>> untermNames) {
        if (rulesWithActions.containsKey(left)) {
            rulesWithActions.get(left).add(new Pair<>(new ArrayList<>(right), untermNames));
        } else {
            List<Pair<List<String>, Map<String, List<String>>>> current = new ArrayList<>();
            current.add(new Pair<>(new ArrayList<>(right), new HashMap<>(untermNames)));
            rulesWithActions.put(left, current);
        }
    }

    public void addLexerRule(String left, String regexp) {
        allRegexps.put(left, new HashSet<>());
        allRegexps.get(left).add(regexp);
        givenRegexps.put(left, regexp);
    }

    public void addSkipRule(String regexp) {
        skipRules.add(regexp);
    }

    public void addInitBlock(String left, String block) {
        initBlocks.put(left, block);
    }

    public void addParameterName(String left, String name) {
        if (localsNamesForUnterm.containsKey(left) && localsNamesForUnterm.get(left).contains(name)) {
            throw new IllegalArgumentException("Parameter name and locals name are the same");
        }
        if (returnsNamesForUnterm.containsKey(left) && returnsNamesForUnterm.get(left).contains(name)) {
            throw new IllegalArgumentException("Parameter name and returns name are the same");
        }
        if (!parametersNamesForUnterm.containsKey(left)) {
            parametersNamesForUnterm.put(left, new HashSet<>());
        }
        parametersNamesForUnterm.get(left).add(name);
    }

    public void addLocalName(String left, String name) {
        if (parametersNamesForUnterm.containsKey(left) && parametersNamesForUnterm.get(left).contains(name)) {
            throw new IllegalArgumentException("Locals name and parameter name are the same");
        }
        if (returnsNamesForUnterm.containsKey(left) && returnsNamesForUnterm.get(left).contains(name)) {
            throw new IllegalArgumentException("Locals name and returns name are the same");
        }
        if (!localsNamesForUnterm.containsKey(left)) {
            localsNamesForUnterm.put(left, new HashSet<>());
        }
        localsNamesForUnterm.get(left).add(name);
    }

    public void addReturnName(String left, String name) {
        if (parametersNamesForUnterm.containsKey(left) && parametersNamesForUnterm.get(left).contains(name)) {
            throw new IllegalArgumentException("Returns name and parameter name are the same");
        }
        if (localsNamesForUnterm.containsKey(left) && localsNamesForUnterm.get(left).contains(name)) {
            throw new IllegalArgumentException("Returns name and locals name are the same");
        }
        if (!returnsNamesForUnterm.containsKey(left)) {
            returnsNamesForUnterm.put(left, new HashSet<>());
        }
        returnsNamesForUnterm.get(left).add(name);
    }

    private Map<String, Set<String>> computeFirst() {
        Map<String, Set<String>> result = new HashMap<>();
        for (String left : rules.keySet()) {
            result.put(left, new HashSet<>());
        }
        boolean changed = true;
        while (changed) {
            changed = false;
            for (String left : rules.keySet()) {
                Set<String> currentFirst = new HashSet<>(result.get(left));
                List<List<String>> currentRules = rules.get(left);
                for (List<String> currentRule : currentRules) {
                    if (currentRule.size() == 0) { // eps
                        currentFirst.add(EPSILON);
                    } else {
                        if (currentRule.get(0).startsWith("!")) {
                            currentFirst.addAll(result.get(currentRule.get(0)));
                        } else {
                            if (currentRule.get(0).startsWith("*")) {
                                int i = 1;
                                String addToFirst = givenRegexps.get(currentRule.get(0));
                                while (i < currentRule.size() && !currentRule.get(i).startsWith("!") && !currentRule.get(i).startsWith("*")) {
                                    if (currentRule.get(i).startsWith("~")) {
                                        i++;
                                        continue;
                                    }
                                    for (int j = 0; j < currentRule.get(i).length(); j++) {
                                        addToFirst += "[" + currentRule.get(i).charAt(j) + "]";
                                    }
                                    i++;
                                }
                                currentFirst.add(addToFirst);
                            } else {
                                int i = 1;
                                String addToFirst = currentRule.get(0);
                                while (i < currentRule.size() && !currentRule.get(i).startsWith("!") && !currentRule.get(i).startsWith("*")) {
                                    if (currentRule.get(i).startsWith("~")) {
                                        i++;
                                        continue;
                                    }
                                    addToFirst += currentRule.get(i);
                                    i++;
                                }
                                currentFirst.add(addToFirst);
                            }
                        }
                    }
                }
                if (!currentFirst.equals(result.get(left))) {
                    result.put(left, currentFirst);
                    changed = true;
                }
            }
        }
        return result;
    }

    private Map<String, Set<String>> computeFollow() {
        Map<String, Set<String>> result = new HashMap<>();
        for (String left : rules.keySet()) {
            result.put(left, new HashSet<>());
        }
        result.get(start).add(RULE_END);
        boolean changed = true;
        while (changed) {
            changed = false;
            for (String left : rules.keySet()) {
                List<List<String>> currentRules = rules.get(left);
                for (List<String> currentRule : currentRules) {
                    int i = 0;
                    for (String rulePart : currentRule) {
                        if (rulePart.startsWith("!")) {
                            Set<String> currentFollow = new HashSet<>(result.get(rulePart));
                            if (i == currentRule.size() - 1) {
                                currentFollow.addAll(result.get(left));
                            } else {
                                String nextPart = currentRule.get(i + 1);
                                if (nextPart.startsWith("!")) {
                                    Set<String> mustAdd = new HashSet<>(first.get(nextPart));
                                    if (mustAdd.contains(EPSILON)) {
                                        currentFollow.addAll(result.get(left));
                                    }
                                    mustAdd.remove(EPSILON);
                                    currentFollow.addAll(mustAdd);
                                } else {
                                    currentFollow.add(nextPart);
                                }
                            }
                            if (!currentFollow.equals(result.get(rulePart))) {
                                result.put(rulePart, currentFollow);
                                changed = true;
                            }
                        }
                        i++;
                    }
                }
            }
        }
        return result;
    }

    public Set<String> getFirstRightPartOfRule(List<String> rightPart) {
        Set<String> result = new HashSet<>();
        if (rightPart.size() == 0) {
            result.add(EPSILON);
        } else {
            String rightFirst = rightPart.get(0);
            int k = 0;
            while (k < rightPart.size() && rightFirst.startsWith("~")) {
                rightFirst = rightPart.get(k);
                k++;
            }
            if (k == rightPart.size()) {
                result.add(EPSILON);
                return result;
            }
            if (rightFirst.startsWith("!")) {
                result = first.get(rightFirst);
            } else {
                String toAdd = rightFirst;
                boolean regexpNow = false;
                if (rightFirst.startsWith("*")) {
                    toAdd = givenRegexps.get(rightFirst);
                    regexpNow = true;
                }
                int i = k + 1;
                while (i < rightPart.size() && !rightPart.get(i).startsWith("!") && !rightPart.get(i).startsWith("*")) {
                    if (rightPart.get(i).startsWith("~")) {
                        i++;
                        continue;
                    }
                    if (regexpNow) {
                        String mustAdd = rightPart.get(i);
                        for (int j = 0; j < mustAdd.length(); j++) {
                            toAdd += "[" + mustAdd.charAt(j) + "]";
                        }
                    } else {
                        toAdd += rightPart.get(i);
                    }
                    i++;
                }
                if (rightFirst.startsWith("*")) {
                    allRegexps.get(rightFirst).add(toAdd);
                }
                result.add(toAdd);
            }
        }
        return result;
    }

    public boolean isLL() {
        first = computeFirst();
        follow = computeFollow();
        for (String left : rules.keySet()) {
            List<List<String>> currentRules = rules.get(left);
            for (List<String> currentRule1 : currentRules) {
                Set<String> first1 = getFirstRightPartOfRule(currentRule1);
                for (List<String> currentRule2 : currentRules) {
                    if (currentRule1.equals(currentRule2)) {
                        if (first1.contains(EPSILON)) {
                            Set<String> currentFollow = follow.get(left);
                            for (String elem : first1) {
                                if (currentFollow.contains(elem)) {
                                    return false;
                                }
                            }
                        }
                        continue;
                    }
                    Set<String> first2 = getFirstRightPartOfRule(currentRule2);
                    for (String elem : first2) {
                        if (first1.contains(elem)) {
                            return false;
                        }
                    }
                    if (first1.contains(EPSILON)) {
                        Set<String> currentFollow = follow.get(left);
                        for (String elem : first2) {
                            if (currentFollow.contains(elem)) {
                                return false;
                            }
                        }
                    }
                }
            }
        }
        return true;
    }

    public Map<String, Set<String>> getFirst() {
        return first;
    }

    public Map<String, Set<String>> getFollow() {
        return follow;
    }

    public Map<String, Set<String>> getAllRegexps() {
        return allRegexps;
    }

    public Set<String> getSkipRules() {
        return skipRules;
    }

    public Map<String, String> getTokens() {
        Map<String, String> resultTokens = new TreeMap<>();
        for (Set<String> regexps : allRegexps.values()) {
            for (String regexp : regexps) {
                resultTokens.put("TOKEN_" + resultTokens.size(), "_regexp" + regexp);
            }
        }
        int i = 0;
        while (i < tokens.size()) {
            resultTokens.put("TOKEN_" + resultTokens.size(), tokens.get("TOKEN_" + i));
            i++;
        }
         resultTokens.put("TOKEN_" + resultTokens.size(), RULE_END);
        return resultTokens;
    }

    public Map<String, String> getStringsToTokenNames() {
        Map<String, String> stringsToTokenNames = new HashMap<>();
        Map<String, String> tokens = getTokens();
        for (Map.Entry<String, String> token : tokens.entrySet()) {
            if (token.getValue().startsWith("_regexp")) {
                stringsToTokenNames.put(token.getValue().substring(7), token.getKey());
            } else {
                stringsToTokenNames.put(token.getValue(), token.getKey());
            }
        }
        return stringsToTokenNames;
    }

    public Map<String, List<Pair<List<String>, Map<String, List<String>>>>> getRulesWithActions() {
        return rulesWithActions;
    }

    public String getStart() {
        return start;
    }

    public Map<String, String> getInitBlocks() {
        return initBlocks;
    }

    public Map<String, Set<String>> getParametersNamesForUnterm() {
        return parametersNamesForUnterm;
    }

    public Map<String, Set<String>> getLocalsNamesForUnterm() {
        return localsNamesForUnterm;
    }

    public Map<String, Set<String>> getReturnsNamesForUnterm() {
        return returnsNamesForUnterm;
    }

    public Set<String> getGivenRegexps() {
        return new HashSet<>(givenRegexps.values());
    }

    public Map<String, String> getGivenRegexpsMap() {
        return givenRegexps;
    }
}
