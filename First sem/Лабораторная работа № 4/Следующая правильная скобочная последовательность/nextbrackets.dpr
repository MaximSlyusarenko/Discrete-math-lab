Program E;

Uses Sysutils, Math;

Var
s: string;
h, b, n, q0, q1, i: integer;

begin
	reset (input, 'nextbrackets.in');
	rewrite (output, 'nextbrackets.out');
	readln(s);
	n := length(s);
	b := 0;
	h := -1;
	for i := n downto 1 do
	begin
		if (s[i] = ')') then
			inc(b)
		else
		if (s[i] = '(') and (b - 1 = 0) then
			dec(b)
		else
		if (s[i] = '(') and (b - 1 > 0) then
		begin
			s[i] := ')';
			h := i;
			break;
		end;
	end;
	if (h = -1) then
	begin
		writeln('-');
		halt;
	end;
	q0 := 0;
	q1 := 0;
	for i := 1 to h do
	begin
		write(s[i]);
		if (s[i] = '(') then
			inc(q0)
		else
			inc(q1);
	end;
	for i := q0 + 1 to n div 2 do
		write('(');
	for i := q1 + 1 to n div 2 do
		write(')');
end.