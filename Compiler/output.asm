include \masm32\include\masm32rt.inc
.data
	buffer db 256 dup(0)
	new_line db 13, 10, 0, 0
.code
factorial proc
	push ebp
	mov ebp,esp
	mov dword ptr [ebp + 12], 0
	cmp dword ptr [ebp + 12], 0
	jne $$L0
	push 0
	inc dword ptr [ebp + 12]
$$L0:
	cmp dword ptr [ebp + 12], 1
	jne $$L1
	push 0
	inc dword ptr [ebp + 12]
$$L1:
	mov edi, 1
	push eax
	mov eax, edi
	mov byte ptr [ebp + 16], al
	pop eax
	cmp dword ptr [ebp + 12], 2
	jne $$L2
	push 0
	inc dword ptr [ebp + 12]
$$L2:
	mov edi, 0
	push eax
	mov eax, edi
	mov byte ptr [ebp + 20], al
	pop eax
$$L3:
	mov edi, dword ptr [ebp + 8]
	xor ebx, ebx
	mov bl, byte ptr [ebp + 20]
	cmp edi, ebx
	je $$L6
	mov edi, 0
	jmp $$L7
$$L6: 
	mov edi, 1
$$L7: 
	xor eax, eax
	add eax, edi
	setz dl
	xor eax, eax
	mov al, dl
	mov edi, eax
	cmp edi, 0
	jne $$L4
	xor ebx, ebx
	mov bl, byte ptr [ebp + 16]
	mov eax, ebx
	push ecx
	mov ecx, dword ptr [ebp + 12]
$$L8:
	pop edx
	dec ecx
	jnz $$L8
	pop ecx
	pop ebp
	ret 4
	jmp $$L5
$$L4:
	push esi
	push ebx
	push ecx
	push eax
	push edx
	mov esi, dword ptr [ebp + 8]
	xor ebx, ebx
	mov bl, byte ptr [ebp + 16]
	sub esi, ebx
	push esi
	call factorial
	mov edi, eax
	pop edx
	pop eax
	pop ecx
	pop ebx
	pop esi
	mov esi, dword ptr [ebp + 8]
	mov eax, esi
	xor edx, edx
	mul edi
	mov esi, eax
	mov eax, esi
	push ecx
	mov ecx, dword ptr [ebp + 12]
$$L9:
	pop edx
	dec ecx
	jnz $$L9
	pop ecx
	pop ebp
	ret 4
$$L5:
factorial endp
printInt proc
	push ebp
	mov ebp,esp
	mov dword ptr [ebp + 12], 0
	cmp dword ptr [ebp + 12], 0
	jne $$L10
	push 0
	inc dword ptr [ebp + 12]
$$L10:
$$L11:
	mov edi, dword ptr [ebp + 8]
	mov esi, 0
	cmp edi, esi
	jne $$L13
	mov edi, 0
	jmp $$L14
$$L13: 
	mov edi, 1
$$L14: 
	xor eax, eax
	add eax, edi
	setz dl
	xor eax, eax
	mov al, dl
	mov edi, eax
	cmp edi, 0
	jne $$L12
	push edi
	push esi
	push ebx
	push ecx
	push eax
	push edx
	mov edi, dword ptr [ebp + 8]
	mov esi, 10
	mov eax, edi
	xor edx, edx
	div esi
	mov edi, eax
	push edi
	call printInt
	pop edx
	pop eax
	pop ecx
	pop ebx
	pop esi
	pop edi
	push edi
	push esi
	push ebx
	push ecx
	push eax
	push edx
	mov edi, dword ptr [ebp + 8]
	mov esi, 10
	mov eax, edi
	xor edx, edx
	div esi
	mov edi, edx
	xor ebx, ebx
	mov bl, '0'
	add edi, ebx
	push edi
	pop edx
	push eax
	mov eax, edx
	mov [buffer], al
	mov [buffer+1], 0
	push offset buffer
	call StdOut
	pop eax
	pop edx
	pop eax
	pop ecx
	pop ebx
	pop esi
	pop edi
$$L12:
	push ecx
	mov ecx, dword ptr [ebp + 12]
$$L15:
	pop edx
	dec ecx
	jnz $$L15
	pop ecx
	pop ebp
	ret 4
printInt endp
getInt proc
	push ebp
	mov ebp,esp
	mov dword ptr [ebp + 8], 0
	cmp dword ptr [ebp + 8], 0
	jne $$L16
	push 0
	inc dword ptr [ebp + 8]
$$L16:
	cmp dword ptr [ebp + 8], 1
	jne $$L17
	push 0
	inc dword ptr [ebp + 8]
$$L17:
	push esi
	push ebx
	push ecx
	push eax
	push edx
	push eax
	push ebx
	push -10
	call GetStdHandle
	mov ebx, eax
	push ebx
	call FlushConsoleInputBuffer
	xor eax, eax
	push 256
	push offset buffer
	call StdIn
	mov al, byte ptr [buffer]
	sub al, '0' 
	mov edi, eax
	pop ebx
	pop eax
	pop edx
	pop eax
	pop ecx
	pop ebx
	pop esi
	push eax
	mov eax, edi
	mov dword ptr [ebp + 12], eax
	pop eax
$$L18:
	cmp dword ptr [ebp + 8], 2
	jne $$L21
	push 0
	inc dword ptr [ebp + 8]
$$L21:
	push esi
	push ebx
	push ecx
	push eax
	push edx
	push eax
	push ebx
	push -10
	call GetStdHandle
	mov ebx, eax
	push ebx
	call FlushConsoleInputBuffer
	xor eax, eax
	push 256
	push offset buffer
	call StdIn
	mov al, byte ptr [buffer]
	sub al, '0' 
	mov edi, eax
	pop ebx
	pop eax
	pop edx
	pop eax
	pop ecx
	pop ebx
	pop esi
	push eax
	mov eax, edi
	mov dword ptr [ebp + 16], eax
	pop eax
	mov edi, 0
	mov edi, dword ptr [ebp + 16]
	mov esi, 0
	cmp edi, esi
	jae $$L22
	mov edi, 0
	jmp $$L23
$$L22: 
	mov edi, 1
$$L23: 
	mov esi, dword ptr [ebp + 16]
	mov ebx, 9
	cmp esi, ebx
	jbe $$L24
	mov esi, 0
	jmp $$L25
$$L24: 
	mov esi, 1
$$L25: 
	xor eax, eax
	test edi, edi
	setz al
	mov edi, eax
	xor eax, eax
	add eax, edi
	setz dl
	xor eax, eax
	mov al, dl
	mov edi, eax
	xor eax, eax
	test esi, esi
	setz al
	mov esi, eax
	xor eax, eax
	add eax, esi
	setz dl
	xor eax, eax
	mov al, dl
	mov esi, eax
	and edi, esi
	xor eax, eax
	add eax, edi
	setz dl
	xor eax, eax
	mov al, dl
	mov edi, eax
	cmp edi, 0
	jne $$L20
	mov edi, 10
	mov esi, dword ptr [ebp + 12]
	mov eax, esi
	xor edx, edx
	mul edi
	mov esi, eax
	mov dword ptr [ebp + 12], esi
	mov edi, dword ptr [ebp + 16]
	mov esi, dword ptr [ebp + 12]
	add esi, edi
	mov dword ptr [ebp + 12], esi
	jmp $$L18
$$L20:
$$L19:
	mov edi, dword ptr [ebp + 12]
	mov eax, edi
	push ecx
	mov ecx, dword ptr [ebp + 8]
$$L26:
	pop edx
	dec ecx
	jnz $$L26
	pop ecx
	pop ebp
	ret 
getInt endp
main proc
	push ebp
	mov ebp,esp
	mov dword ptr [ebp + 8], 0
	cmp dword ptr [ebp + 8], 0
	jne $$L27
	push 0
	inc dword ptr [ebp + 8]
$$L27:
$$L28:
	cmp dword ptr [ebp + 8], 1
	jne $$L31
	push 0
	inc dword ptr [ebp + 8]
$$L31:
	push esi
	push ebx
	push ecx
	push eax
	push edx
	call getInt
	mov edi, eax
	pop edx
	pop eax
	pop ecx
	pop ebx
	pop esi
	push eax
	mov eax, edi
	mov byte ptr [ebp + 12], al
	pop eax
	mov edi, 0
	xor ebx, ebx
	mov bl, byte ptr [ebp + 12]
	mov edi, 0
	cmp ebx, edi
	jae $$L32
	mov ebx, 0
	jmp $$L33
$$L32: 
	mov ebx, 1
$$L33: 
	xor eax, eax
	add eax, ebx
	setz dl
	xor eax, eax
	mov al, dl
	mov ebx, eax
	cmp ebx, 0
	jne $$L30
	cmp dword ptr [ebp + 8], 2
	jne $$L34
	push 0
	inc dword ptr [ebp + 8]
$$L34:
	push esi
	push ebx
	push ecx
	push eax
	push edx
	xor ebx, ebx
	mov bl, byte ptr [ebp + 12]
	push ebx
	call factorial
	mov edi, eax
	pop edx
	pop eax
	pop ecx
	pop ebx
	pop esi
	push eax
	mov eax, edi
	mov dword ptr [ebp + 16], eax
	pop eax
	push edi
	push esi
	push ebx
	push ecx
	push eax
	push edx
	mov edi, dword ptr [ebp + 16]
	push edi
	call printInt
	pop edx
	pop eax
	pop ecx
	pop ebx
	pop esi
	pop edi
	push edi
	push esi
	push ebx
	push ecx
	push eax
	push edx
	mov edi, 13
	push edi
	pop edx
	push eax
	mov eax, edx
	mov [buffer], al
	mov [buffer+1], 0
	push offset buffer
	call StdOut
	pop eax
	pop edx
	pop eax
	pop ecx
	pop ebx
	pop esi
	pop edi
	push edi
	push esi
	push ebx
	push ecx
	push eax
	push edx
	mov edi, 10
	push edi
	pop edx
	push eax
	mov eax, edx
	mov [buffer], al
	mov [buffer+1], 0
	push offset buffer
	call StdOut
	pop eax
	pop edx
	pop eax
	pop ecx
	pop ebx
	pop esi
	pop edi
	jmp $$L28
$$L30:
$$L29:
	mov edi, 0
	mov eax, edi
	push ecx
	mov ecx, dword ptr [ebp + 8]
$$L35:
	pop edx
	dec ecx
	jnz $$L35
	pop ecx
	pop ebp
	ret 
main endp
start:
	call main
end start
