void Swap(int* a, int n, int i)
{
	//Vun dong cay co goc la chi so i
	if (i >= n / 2)
	{
		return; //Nut la roi cha co gi ma lam ca
	}else
	{
		int max = a[2 * i + 1];
		int k = 2 * i + 1;
		if (2 * i + 2 < n && max < a[2 * i + 2])
		{
			max = a[2 * i + 2];
			k = 2 * i + 2;
		}
		if (a[i] < max)
		{
			DoiCho(a, i, k);
			Swap(a, n, k);
		}
	}
}

void HeapSort(int* a, int n)
{
	if (n == 1)
	{
		return; //Het roi ko con gi phai lam
	}else
	{
		int j = n / 2 - 1; //Chi so cua nut goc duoi cung
		for (int i = j;i >= 0;i--)
		{
			Swap(i);
		}
		DoiCho(0, n - 1);
		HeapSort(a, n - 1);
	}
}
