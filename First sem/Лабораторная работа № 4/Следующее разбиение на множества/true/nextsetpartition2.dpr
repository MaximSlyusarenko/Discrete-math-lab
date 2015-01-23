Program p1;

Uses Sysutils, Math;

Var i, j, r, code, q, g, maxi, t, f, mini, d, b, e, p: integer; n, k: int64;
a: array[0..2010, 0..2010] of int64;
kol: array[0..2010] of int64;
used: array[1..2010] of boolean;
s, s1: string;
flag, fl: boolean;

begin
	reset (input, 'nextsetpartition.in');
	rewrite (output, 'nextsetpartition.out');
	readln(n, k);
	i := 0;
	for j := 1 to n do
		used[j] := true;
	while (n <> 0) and (k <> 0) do
	begin
		for j := 1 to n do
			used[j] := true;
		j := 0;
		readln(s);
		r := 1;
		while (r <= length(s)) do
		begin
			q := r;
			while (s[q] <> ' ') and (q <= length(s)) do
				inc(q);
			s1 := copy(s, r, q - r);
			val(s1, a[i][j], code);
			inc(j);
			r := q + 1;
		end;
		kol[i] := j;
		inc (i);
		if (i = k) then
		begin
			q := k - 1;
			maxi := -1;
			flag := true;
			while (q >= 0) and (flag) do
			begin
				maxi := max(maxi, a[q][kol[q] - 1]);
				if (maxi = a[q][kol[q] - 1]) then
					t := q;
				fl := false;
				for g := kol[q] - 1 downto 0 do
				begin
					if (a[q][g] < maxi) and not((t = q) and (kol[t] = 2)) then
					begin
						r := a[q][g];
						d := g;
						b := q;
						fl := true;
						break;
					end;
				end;
				if (fl) then
				begin
					mini := 1000000;
					for i := q to k - 1 do
					begin
						for g := 0 to kol[i] - 1 do
							if (a[i][g] > r) and (a[i][g] < mini) then
							begin
								mini := a[i][g];
								f := i;
								e := g;
							end;
					end;
					if (d = kol[b] - 1) then
					begin
						a[b][d + 1] := a[f][e];
						inc(kol[b]);
						for i := 0 to b do
							for g := 0 to kol[i] - 1 do
								used[a[i][g]] := false;
						p := b + 1;
						for i := 1 to n do
							if (used[i]) then
								inc(p);
						writeln(n, ' ', p);
						for i := 0 to b do
						begin
							for g := 0 to kol[i] - 1 do
								write(a[i][g], ' ');
							writeln;
						end;
						for i := 1 to n do
							if (used[i]) then
								writeln(i);
						flag := false;
					end
					else
					begin
						a[b][d] := a[f][e];
						kol[b] := d + 1;
						for i := 0 to b do
							for g := 0 to kol[i] - 1 do
								used[a[i][g]] := false;
						p := b + 1;
						for i := 1 to n do
							if (used[i]) then
								inc(p);
						writeln(n, ' ', p);
						for i := 0 to b do
						begin
							for g := 0 to kol[i] - 1 do
								write(a[i][g], ' ');
							writeln;
						end;
						for i := 1 to n do
							if (used[i]) then
								writeln(i);
						flag := false;
					end;
				end;
				dec(q);
			end;
			if (flag) then
			begin
				writeln(n, ' ', n);
				for i := 1 to n do
					writeln(i);
			end;
			i := 0;
			writeln;
			readln;
			readln(n, k);
		end;
	end;
end.