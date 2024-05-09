#include <stdio.h>

//declaramos e inicializamos las siguientes constantes de manera global:
const float domiciliario = 10.0f,
	industrial = 50.0f,
	monticulo = 30.0f,
	chofer = 100.0f,
	levantador = 80.0f,
	costoGasoil = 25.0;

// en esta funcion calculamos el costo unicamnente del personal:
 
float costoPersonal(){
	float costo = chofer + (levantador * 2);
	return costo;
}

// aqui vamos a calcular el costo base del servicio que incluye costo ya sea por cuadra
//o toneladas segun corresponda por el tipo de servicio solicitado por el usuario:

float costoBase(float cantUnidades, int tipoServi){
	float costo ;
	switch(tipoServi){
		case 1:
			costo = cantUnidades * domiciliario;
			break;
		case 2:
			costo = cantUnidades * industrial;
			break;
		case 3: 
			costo = cantUnidades * monticulo;
			break;
	}
	return costo;
}
// aqui calculamos el costo que habra en combustible :

float costoCombustible(float cantUnidades, int tipoServi){
	
	float combustibleCuadras = 0.2,
		combustibleToneladas = 0.5,
		litrosCombustible,
		costo;
		
	if(tipoServi == 1){
		litrosCombustible = (((cantUnidades * 1)/100) * combustibleCuadras) / 1;
	}else{
		litrosCombustible = (cantUnidades * combustibleToneladas) / 1;
	}
	
	costo = (litrosCombustible * costoGasoil)/1;
	return costo;
}

//funcion para ir acomulando las facturaciones e cada servicio
//asi luego mostramos el total de facturacion al minicipio: sera una funcion de parametro por referencia

void facturacionMunicipio(float costoServicio, float *facturaMunicipio){
	*facturaMunicipio += costoServicio;
}

void main(){
	int seguir,
		tipoServicio,
		llueve;
		
	float costoServicio = 0,
		cantUnidades,
		facturaMunicipio = 0;
	
	do{
		printf("----------------------------------------------\n    !BIENVENIDO A SERVICIOS AMBIENTALES! \n----------------------------------------------\n¿Desea solicitar algun servicio? 1(si) 0(no)\n");
		scanf("%d", &seguir);
	}while(seguir != 1 && seguir != 0);
	
	while(seguir == 1){
		
		//pedimos y validamos los datos necesarios para solicitar el servicio:
		do{
			printf("Ingresa el tipo de servicio que deseas solicitar:\n  \n1- Domiciliario \n2- Industrial \n3- Monticulo\n");
			scanf("%d", &tipoServicio);
		}while(tipoServicio != 1 && tipoServicio != 2 && tipoServicio != 3);
		
		do{
			printf("Esta pronosticado lluvia para el dia? 1(si) 0(no)\n");
			scanf("%d", &llueve);	
		}while(llueve != 1 && llueve != 0);
		
		//verificamos el tipo de servicio solicitado por el cliente junto con la validacion y  luego llamamos a
		//la funcion costo base para calcular el costo base segun cada servicio:
		switch(tipoServicio){
			case 1:
				do{
					printf("Ingresa la cantidad de cuadras\n");
					scanf("%f", &cantUnidades);
				}while(cantUnidades < 0);
				costoServicio = costoBase(cantUnidades, tipoServicio);
				break;
			case 2:
				do{
					printf("Ingresa la cantidad de toneladas\n");
					scanf("%f", &cantUnidades);
				}while(cantUnidades < 0);
				costoServicio = costoBase(cantUnidades, tipoServicio);
				break;
			case 3:
				do{
					printf("Ingresa la cantidad de toneladas\n");
					scanf("%f", &cantUnidades);
				}while(cantUnidades < 0);
				costoServicio = costoBase(cantUnidades, tipoServicio);
				break;
		}
		
		//limpiamos la consola asi mostramos la factura del servicio limpia:
		system("cls");
		//mostramos la factura del servicio:
		printf("-------------------------------------------------------------------------------------------\n                              FACTURA DE SERVICIO\n-------------------------------------------------------------------------------------------\n \n-------------------------------------------------------------------------------------------\nCosto del servicio base(sin combustible ni personal): %.2f $\nCosto del combustible: %.2f $ \nCosto del personal: %.2f $\n", costoServicio, costoCombustible(cantUnidades, tipoServicio), costoPersonal());
		costoServicio += costoPersonal() + costoCombustible(cantUnidades, tipoServicio);
		
		//Aqui verificamos si es dia de lluvia o no y efectuamos o no la suma del 50% del costo del servicio
		// dicho costo es solo tomando en cuanta el costo base con el costo de personal:
		if(llueve == 1){
			costoServicio += (50 * costoServicio) / 100;
			printf("Costo del servicio incluyendo personal y gasto de combustible y dia de lluvia: %.2f $\n", costoServicio);
		}
		//mostramos el costo total del servicio:
		printf("Costo total del servicio: %.2f $\n-------------------------------------------------------------------------------------------\n \n-------------------------------------------------------------------------------------------\n", costoServicio);
		
		//le agregamos al acumulador el costo de cada servicio realizado, este costo
		//incluye todos los gastos del servicio:
		
		facturacionMunicipio(costoServicio, &facturaMunicipio);
		
		printf("!Gracias por solicitar nuestros servicios!\n");
		//preguntamos si se desea realizar otro servicio:
		do{
			printf("Deseas solicitar otro servicio? 1(si) 0(no)");
			scanf("%d", &seguir);	
		}while(seguir != 1 && seguir != 0);
		
		//limpiamos la consola:
		system("cls");
	}
	system("cls");
	printf("-------------------------------------------\n                   FACTURA\n-------------------------------------------\n-------------------------------------------\n\nTotal de facturacion: %.2f $\n \n-------------------------------------------\n-------------------------------------------\n", facturaMunicipio);
}

