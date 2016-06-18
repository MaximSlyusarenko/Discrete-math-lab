Program p;

Uses Sysutils, Math;

Var i, j, r, code, q, g1, h1, g, h, maxi, tmp, f, mini, d, b, e: integer; n, k: int64;
a: array[0..5, 0..5] of int64;
kol: array[0..5] of int64;
used: array[1..5] of boolean;
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
		//for r := 0 to j - 1 do
		//	write(a[i][r], ' ');
		//writeln;
		kol[i] := j;
		inc (i);
		if (i = k) then
		begin
			q := i;
			maxi := -1;
			flag := true;
			while (q > 0) and (flag) do
			begin
				maxi := max(maxi, a[q - 1][kol[q] - 1]);
				dec(q);
				fl := false;
				for g := kol[q] - 1 downto 0 do
				begin
					if (a[q][g] < maxi) then
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
					inc(q);
					for i := q to k - 1 do
						for g := 0 to kol[i] - 1 do
							if (a[i][g] > r) and (a[i][g] < mini) then
							begin
								mini := a[i][g];
								f := i;
								e := g;
							end;
					if (d = kol[b] - 1) then
					begin
						a[b][d + 1] := a[f][e];
						inc(kol[b]);
						for i := 0 to b do
						begin
							for g := 0 to kol[i] - 1 do
							begin
								write(a[i][g], ' ');
								used[a[i][g]] := false;
							end;
							writeln;
						end;
						for i := 1 to n do
							if (used[i]) then
								writeln(i);
					end
					else
					begin
						a[b][d] := a[f][e];
						kol[b] := d + 1;
						for i := 0 to b do
						begin
							for g := 0 to kol[i] - 1 do
							begin
								write(a[i][g], ' ');
								used[a[i][g]] := false;
							end;
							writeln;
						end;
						for i := 1 to n do
							if (used[i]) then
								writeln(i);
					end;
					//tmp := a[f][e];
					//a[f][e] := a[b][d];
					//a[b][d] := tmp;
					//swap(a[f][e], a[b][d]);
					//fl := true;
					//for i := f to d - 1 do
					//	if (a[i][0]	> a[i + 1][0]) then
					//		fl := false;
					//if (not fl) then
					//begin
					//	tmp := a[f][e];
					//	a[f][e] := a[b][d];
					//	a[b][d] := tmp;
					//	a[b][d + 1] := a[f][e];
					//	inc(kol[b]);
					//	for i := 0 to b do
					//	begin
					//		for g := 0 to kol[i] - 1 do
					//		begin
					//			writeln(a[i][g]);
					//			used[a[i][g]] := false;
					//		end;
					//		writeln;
					//	end;
					//	for i := 1 to n do
					//		if (used[i]) then
					//			writeln(i);
						//swap(a[f][e], a[b][d]);
					//	dec(q);
					//end
					//else
					//begin
					//	flag := false;
						//вывод
					//	for i := 0 to k - 1 do
					//	begin
					//		for g := 0 to kol[i] - 1 do
					//			write(a[i][g], ' ');
					//		writeln;
					//	end;
					//end;
				end;
			end;
			i := 0;
			writeln;
			readln;
			readln(n, k);
		end;
	end;
end.