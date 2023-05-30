const VariableType = enum { string, int, ptr };

const VariableValue = union(VariableType) { string: []u8, int: i32, ptr: *u8 };

const Assignment = struct { name: []u8, value: VariableValue };

const StatementType = enum { assignment, function, import, exports, call };
const Statement = union(StatementType) { assignment: Assignment };
