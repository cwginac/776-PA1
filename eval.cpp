double eval(int *pj)
{
	double score = 0;
	for(int i = 0; i < 100; i++)
	{
		if ((i%2) == 0 && pj[i] == 1)
		{
			score++;
		}
		else if ((i%2) != 0 && pj[i] == 0)
		{
			score++;
		}	
	}
	
	return score;
}

