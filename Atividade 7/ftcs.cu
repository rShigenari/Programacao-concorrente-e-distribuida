#include <stdio.h>
#include <cuda.h>
#include <time.h>
#include <sys/time.h>

/* constantes numericas para calculo do metodo ftcs */
#define tam 1.0
#define dx 0.00001
#define dt 0.000001
#define T  0.01
#define kappa 0.000045


typedef long long int lli;

__global__ void funcaoCalcula(double *u, double *prev, double kap, double dt, double dx, int s){
	lli i =  blockDim.x * blockIdx.x + threadIdx.x;
	if(i>0 && i<(s-1))
		u[i] = prev[i] + kap*dt/(dx*dx)*(prev[i-1]-2*prev[i]+prev[i+1]);
}

__global__ void funcaoContorno(double *u, int n){
	lli i =  blockDim.x * blockIdx.x + threadIdx.x;
	if(i==1)
        u[0] = u[n] = 0.0;
}

int main(){
    /* variaveis do host */
	double t = 0.0, x = dx,  tmiliCuda;
	double  *u, *u_prev, *temp;
	lli i, n, maior, tam_blocos, tam;
    struct timeval inicioCuda, fimCuda;

	double *aux, *u_prev_prev; //variaveis do device


	n = tam/dx; //quantidade de pontos


   	 tam_blocos = ceil((n+1)/512);// calcula quantidade de blocos 

	/* aloca vetores no host */
    tam = (n+1)*sizeof(double);
	u = (double *) malloc(tam);
	u_prev = (double *) malloc(tam);

    /* preenche vetor u_prev no host */
	for(i=1; i<n; i++){
		if(x<=0.5) 
			u_prev[i] = 200.0*x;
		else        
			u_prev[i] = 200.0*(1.0-x);
		x += dx;
	}

    /* aloca vetores no device */
	cudaMalloc((void **)&aux, tam);
	cudaMalloc((void **)&u_prev_prev, tam);


	cudaMemcpy(u_prev_prev, u_prev, tam, cudaMemcpyHostToDevice); //copia valores do vetor u_prev do host para o u_prev_prev do device

    gettimeofday(&inicioCuda,NULL); //conta o tempo inicial do processamento para a medida de desempenho

	while(t<T){
		funcaoCalcula<<<tam_blocos, 512>>>(u_ua, u_prev_prev, kappa, dt, dx, n+1); //processamento paralelo no device	
      	        cudaDeviceSynchronize(); //sincroniza o processamento no device para que possa realizar a troca de ponteiros antes da proxima iteracao
		funcaoContorno<<<tam_blocos,512>>>(aux, n);//condicao de contorno
		temp = aux; // realiza a troca de ponteiros, atualizando a proxima iteracao
		aux = u_prev_prev;
	    	u_prev_prev = temp;

	   	t += dt; //atualiza variavel de controle da estrutura de repeticao
	}
   	gettimeofday(&fimCuda,NULL);//obtem o tempo final do processamento
	cudaMemcpy(u, aux, tam, cudaMemcpyDeviceToHost);//copia os valores do vetor aux para o vetor u do host

	maior= 0; //acha o maior valor e a posicao do vetor
	for(i=1; i<n+1; ++i)
		if(u[i] > u[maior])
            maior= i;
    
    tmiliCuda = (double)(1000.0*(fimCuda.tv_sec-inicioCuda.tv_sec)+(fimCuda.tv_usec-inicioCuda.tv_usec)/1000.0);//calcula tempo de processamento

    printf("FTCS :: CUDA(CPU+GPU)\n");
    printf("Maximo valor de u[%lld] = %g\n", maior, u[maior]);
    printf("%lld Pontos e %lld Iteracoes\n", (n+1), (lli)(T/dt));
    printf("%lld Blocos e %lld Numero de threads por bloco\n", tam_blocos, (lli)512);
    printf("Tempo =  %.3lf ms\n", tmiliCuda);

    free(u); //libera memoria no host
    free(u_prev);
    u = NULL;
    u_prev = NULL;

    cudaFree(aux);//libera memoria no device
    cudaFree(u_prev_prev);

    return 0;
}
