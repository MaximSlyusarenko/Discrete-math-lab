Program p1;

Uses Sysutils, Math;

Var 
n, q0, q1: integer;
s2: string;

procedure gen(s: string; b, q0, q1: integer);
var s1: string;
begin
	if (q0 = n) and (q1 = n) then
		writeln(s);
	if (q0 < n) then
	begin
		s1 := s + '(';
		gen(s1, b + 1, q0 + 1, q1);
	end;
	if (q1 < n) and (b > 0) then
	begin
		s1 := s + ')';
		gen(s1, b - 1, q0, q1 + 1);
	end;
end;

begin
	reset (input, 'brackets.in');
	rewrite (output, 'brackets.out');
	readln(n);
	s2 := '';
	gen(s2, 0, 0, 0);
end.