# Datalog-Interpreter-with-Relations

the major steps of the interpreter are:

Process the schemes (same as the last project)
Process the facts (same as the last project)
Evaluate the rules (add more code as described below)
Evaluate the queries (same as the last project)

The following steps are used to evaluate the rules:

Build the dependency graph.
Build the reverse dependency graph.
Run DFS-Forest on the reverse dependency graph.
Find the strongly connected components (SCCs).
Evaluate the rules in each component.
Dependency Graph
Build the dependency graph for the rules in the Datalog program.

Assign a numeric identifier to each rule starting with zero. Assign the identifiers to the rules in the order the rules appear in the input. Use 0 for the first rule, 1 for the second rule, etc.

When outputting rule identifiers always precede the rule identifier with the letter R. For example, output the first rule as R0, the second rule as R1, etc. The preceding R is for decoration only and is not part of the identifier.

Make a node in the graph for each rule identifier. Don't add the same node to the graph more than once.

Make an edge in the graph for each rule dependency. Add an edge to the graph from node x to node y if the evaluation of x depends on the result of y. Rule A depends on rule B if any of the predicate names in the body of rule A is the same as the predicate name of the head of rule B. Don't add the same edge to the graph more than once.

Note that more than one rule may have the same predicate name in the head. This means that a single name in the body of a rule may cause a dependency on more than one rule.

Note also that a rule may depend on itself.

FS Forest
The next step of the SCC algorithm is to run DFS-Forest on the reverse dependency graph to obtain post-order numbers.

Run DFS-Forest on the reverse dependency graph. Assign postorder numbers to each node visited in the search starting with a postorder number of 1. When there is a choice of which node to visit next, choose the node identifier that comes first numerically.

The post-order numbers for the example from the previous section are:

  R0: 3
  R1: 2
  R2: 1
  R3: 5
  R4: 4
(Note that the only result from this step that is actually needed by the next step is a list of the nodes in order from largest to smallest post-order number. Thus this step is effectively computing a topological sort of the nodes in the reverse graph. This ordering can actually be found without assigning post-order numbers to the nodes. The correct order can be obtained more easily by pushing each node ID on a stack at the point where a post order number would be assigned to the node. In the example, you would push R2 first, followed by R1, R0, R4, and R3. The resulting stack would store the nodes in the order: R3, R4, R0, R1, R2. Thus the stack would contain the nodes in the needed order. You are encouraged to use the stack approach and not actually assign post-order numbers.)

Finding the SCCs
The post-order numbers from the DFS-Forest on the reverse graph give the correct order to use for searching for SCCs in the original dependency graph. The order used is from largest post-order number to smallest post-order number.

The first SCC is found by running a depth-first search on the original dependency graph starting from the node with the largest post-order number. Any node visited during the DFS is part of the SCC.

For the example from the previous section, the search starts at node R3 and visits only node R3. The first SCC contains only node R3.

The process is repeated with the other nodes in order of decreasing post-order number.

The search for the second SCC starts at node R4 and visits only node R4. The second SCC contains only node R4.

The search for the next SCC starts at node R0 and visits nodes R0, R1, and R2. The SCC contains nodes R0, R1, and R2.

The process attempts to find additional SCCs starting with node R1 and then node R2. Since these nodes have already been visited, additional SCCs are not found.

Note that the visit markers used in the depth-first search must not be reset between the searches for each SCC.

SCC Evaluation
For each SCC found in the previous step, run the rule evaluation process from the previous project on the subset of rules found in the SCC.

Evaluate the SCCs in the order they are found.

If an SCC contains only one rule and that rule does not depend on itself, evaluate the rule only once.

If an SCC contains more than one rule or a single rule that depends on itself, repeat the evaluation of the rules until the evaluation reaches a fixed point.

When an SCC contains more than one rule, evaluate the rules in the SCC in the numeric order of the rule identifiers.
