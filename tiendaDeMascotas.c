#include <stdio.h>
#include <string.h>
#include <unistd.h>

//declaramos e inicializamos los arreglos que contendran los productos segun su tipo:
//use punteros de arreglo asi se crea un arreglo de estrings *nombreArreglo[] ={"","",....} seran variables globales:

char *alimentoBalanceado[] = {"Royal Canin", "Club Performance", "Nutrique"};
char *textiles[] = {"Vestimenta", "Almohadones", "Mantas"};
char *articulosVarios[] = {"Cuchas", "correas", "Bozales", "Juguetes"};

/*La siguiente funcion se encarga de mostrar listas de productos segun el tipo de produccto
seleciona por el usuario y le asignamos el nombre por referencia a la variable 
nombreProducto y a cantUnidades. Recuerda por referencia signififca que afecta el valor de la variable principal */
void opcionProductoUser(int tipoProducto, char *nombreProducto, float *precioUnitario, int *cantUnidades) {
	
	//declaramos e inicializamos la variable i que sera la que usaremos para iterar los arreglos
    int i = 0, producto;

	printf("----------------------------------------\n         BIENVENIDO A PET SHOP\n----------------------------------------\n \n");
    printf("PRODUCTOS DISPONIBLES: \n------------------------------------\n");

    switch (tipoProducto) {
        case 1:
        	/*mostramos la lista especifica del tipo de producto seleccionado
			para esto recorremos los arreglos con un for y en cada iteracion se muestra el elemento de dicha posicion*/
            for (i = 0; i < sizeof(alimentoBalanceado) / sizeof(alimentoBalanceado[0]); i++) {
                printf("%d- %s \n", (i + 1), alimentoBalanceado[i]);
            }
            printf("\n------------------------------------\n");
            //limpiamos el buffer para evitar errores en el scanf
            fflush(stdin);
            //solicitamos el producto:
            scanf("%d", &producto);
            //solicitamos precio y cantidad de unidades del producto:
            printf("Ingresa el precio Unitario: \n");
            scanf("%f", precioUnitario);
            
            printf("Ingresa la cantidad de unidades\n");
            scanf("%d", cantUnidades);
            
            /*recorro de vuelta el arreglo correspondiente con el sizeof obtenemos el tamaño en bytes del arreglo
			para obtener su tamaño de elemento usamos el sizeof(arreglo) / sizeof(arreglo[0])
			o sea el tamaño en bytes entre el tamaño en bytes de uno de sus elementos puede ser cualquier elemento*/
            for (i = 0; i < sizeof(alimentoBalanceado) / sizeof(alimentoBalanceado[0]); i++) {
            	//verifico si el producto seleccionado es igual al que se esta iterando :
                if (producto == (i + 1)) {
                	/*asigno el nombre del producto iterado i al nombreProducto:
					usamos la funcion strcpy(nombreVariable, valor)*/
                    strcpy(nombreProducto, alimentoBalanceado[i]);
                    break;
                }
            }
            break;
        //realizo exactamente lo mismo con los demas tipos, esto se puede optimizar DESPUES LO HAGO
        case 2:
            for (i = 0; i < sizeof(textiles) / sizeof(textiles[0]); i++) {
                printf("%d- %s \n", (i + 1), textiles[i]);
            }
            
            printf("\n------------------------------------\n");
            fflush(stdin);
            scanf("%d", &producto);
            
            printf("Ingresa el precio Unitario: \n");
            scanf("%f", precioUnitario);
            
            printf("Ingresa la cantidad de unidades\n");
            scanf("%d", cantUnidades);
            
            for (i = 0; i < sizeof(textiles) / sizeof(textiles[0]); i++) {
                if (producto == (i + 1)) {
                    strcpy(nombreProducto, textiles[i]);
                    break;
                }
            }
            break;
        case 3:
            for (i = 0; i < sizeof(articulosVarios) / sizeof(articulosVarios[0]); i++) {
                printf("%d- %s \n", (i + 1), articulosVarios[i]);
            }
            
            printf("\n------------------------------------\n");
            fflush(stdin);
            scanf("%d", &producto);
            
            printf("Ingresa el precio Unitario: \n");
            scanf("%f", precioUnitario);
            
            printf("Ingresa la cantidad de unidades\n");
            scanf("%d", cantUnidades);
            
            for (i = 0; i < sizeof(articulosVarios) / sizeof(articulosVarios[0]); i++) {
                if (producto == (i + 1)) {
                    strcpy(nombreProducto, articulosVarios[i]);
                    break;
                }
            }
            break;
    }
}

//funcion de factura de compra: que calculara el total a pagar por el cliente aplicnado o no descuentos
float calculoMontoTotal(int tipoProducto, int origenProducto, float costoBase, int cantUnidades, int codProducto, float *totalDescuentos, float *totalImpuestos){
	
	/*declaramos e inicializamos las variables que usaremos para calcular el costo total
	de la venta aplicando descuento o recargas bien sea el caso*/
	float costoTotal = costoBase,
		recargaImportados = 0,
		porcentajeCod300 = 0,
		porcentaje2x1 = 0;
	//verificamos si el producto es importado y si es asi sumarle el 20%
	if(origenProducto == 2){
		recargaImportados =( 20 * costoBase)/ 100;
		costoTotal += recargaImportados;
		*totalImpuestos +=  recargaImportados;
	}
	//verificamos el tipo de producto 
	switch(tipoProducto){
		case 1:
			/*verificamos que si se pueda hacer el dos por uno 
			o sea tenemos que verificar que la cantidad de productos sea par y hacer el descuento*/
			if(cantUnidades %2 == 0){
				porcentaje2x1 = (50 * costoBase)/ 100;
				costoTotal -= porcentaje2x1;
				*totalDescuentos += porcentaje2x1;
			}
			break;
		case 2:
			/*verificamos si el producto de tipo textil tiene un codigo mayor al 300 
			y de ser asi aplicamos el descuento espesificado del 5 %*/
			if(codProducto > 300){
				porcentajeCod300 = (5 * costoBase) / 100;
				costoTotal -= porcentajeCod300;
				*totalDescuentos += porcentajeCod300;
			}
			break;
	}
	//retornamos el valor costoTotal que sera el valor que debera pagar el cliente
	return costoTotal;
}
//funcion para calcular cual es el producto mas caro vendido:
void masCaro(char nombreProducto[20], char *productoMasCaro, float precioProducto, float *precioProductCaro) {
    if (precioProducto > *precioProductCaro) {
        strcpy(productoMasCaro, nombreProducto); // Copia el nombre del producto más caro
        *precioProductCaro = precioProducto; // Asigna el precio del producto más caro
    }
}

//la siguiente funcion lo que hara sera ir acumulando los  tickets y sumando los precios base respectivamente:
void calculoVentasYTickets(int tipoProducto, int *ticketsAlimentos, int *ticketsTextiles, int *ticketsVarios, float *vendidoAlimentos, float *vendidoTextiles, float *vendidoVarios, float costoBase, int cantUnidades){
	switch(tipoProducto){
		case 1:
			*ticketsAlimentos += cantUnidades;
			*vendidoAlimentos += costoBase;
			break;
		case 2:
			*ticketsTextiles += cantUnidades;
			*vendidoTextiles += costoBase;
			break;
		case 3:
			*ticketsVarios += cantUnidades;
			*vendidoVarios += costoBase;
			break;
	}
}

void main() {
	//declaramos las variables de entrada y de procesamiento e inicializamos en caso de ser necesario:
    int tipoProducto, 
		nroTicket,
	 	codProducto,
	  	origenProducto,
	  	cantUnidades,
	  	seguir;
	
	float  precioUnitario,
		costoBase,
		costoTotalCliente,
		precioProductCaro = 0;
	
	//declaramos e inicializamos los contadores y acumuladores
	float totalDescuentos = 0,
		totalImpuestos = 0,
		vendidoAlimentos = 0,
		vendidoTextiles = 0,
		vendidoVarios = 0;
		
	int ticketsAlimentos = 0,
		ticketsTextiles = 0,
		ticketsVarios = 0;
	
	//esta variable la usaremos para que en ella se gurde el nombre del producto que se compre:
    char nombreProducto[20],
		productoMasCaro[20];
    //pregunto y valido si desea el cliente iniciar su compra:
    do{
    	printf("----------------------------------------\n         BIENVENIDO A PET SHOP\n----------------------------------------\n \nDeseas empezar a comprar? 1(si) 0(n0)\n");
        scanf("%d", &seguir);
	}while(seguir != 1 && seguir != 0);
    
    //limpiamos la pantalla:
    system("cls");
    //si el cliente desea iniciar la compra entramos al while:
	while(seguir == 1){
		
		printf("----------------------------------------\n         BIENVENIDO A PET SHOP\n----------------------------------------\n \n");
		
		// a continuacion ingresamoas los datos y validamos respectivamente:
    	printf("Ingresa el numero de ticket\n");
   		scanf("%d", &nroTicket);

    	printf("Ingresa el codigo del producto\n");
    	scanf("%d", &codProducto);

    	do {
      	  printf("\nIngresa el tipo de producto: \n-------------------------------\n1 - Alimentos Balanceados \n2 - Textiles \n3 - Articulos varios\n-------------------------------\n");
      	  scanf("%d", &tipoProducto);
      	  fflush(stdin);
    	} while (tipoProducto != 1 && tipoProducto != 2 && tipoProducto != 3);
    	
    	// verificamos si es importado o nacional:
		do{
			printf("Origen del producto:\n------------------------\n1(Nacional) \n2(Importado)\n------------------------\n");
			scanf("%d", &origenProducto);
		}while(origenProducto != 1 && origenProducto != 2);
		
		//limpiamos la pantalla:
		system("cls");
		
		//llamamos a la funcion que mustra los productos:
    	opcionProductoUser(tipoProducto, nombreProducto, &precioUnitario, &cantUnidades);

		costoBase = cantUnidades * precioUnitario;
		
		//le asignamks el valor que retorna la funcion de calcularMontoTotal a costoTotalCliente
		costoTotalCliente = calculoMontoTotal(tipoProducto, origenProducto, costoBase, cantUnidades,codProducto, &totalDescuentos, &totalImpuestos);
		
		//buscamos el producto mas caro:
		masCaro(nombreProducto, &productoMasCaro, precioUnitario, &precioProductCaro);
		
		//limpiamos consola
		system("cls");
		//mostramos el recibo de pago por pantalla
		printf("Procesando tu compra ........");
		//usamos la funcion Sleep para esperar unos segundos antes de mostrar el recibo
		//de compra, recuerda agregar la libreria #include <unistd.h>
		Sleep(2000);
		//limpiamos consola
		system("cls");
		
    	printf("----------------------------------\n        FACTURA DE COMPRA \n----------------------------------\n----------------------------------\nProducto seleccionado: %s\nPrecio unitario: %.2f $\nCantidad de unidades compradas: %d\nMonto sin descuentos: %.2f $\nTOTAL: %.2f $\n----------------------------------\n----------------------------------\n", nombreProducto, precioUnitario, cantUnidades, costoBase, costoTotalCliente);
    	
    	//llamamos a la funcion calculoVentasYTickets:
    	calculoVentasYTickets(tipoProducto, &ticketsAlimentos, &ticketsTextiles, &ticketsVarios, &vendidoAlimentos, &vendidoTextiles, &vendidoVarios, costoBase, cantUnidades);
	    
    	do{
    		printf("Deseas iniciar otra compra? 1(si) 0(no)\n");
    		scanf("%d", &seguir);
		}while(seguir != 1 && seguir != 0);
		
		//limpiamos la pantalla para la siguiente compra:
    	system("cls");
	}
	printf("Espera un momento mientras hacemos los calculos administratiuvos.........");
	Sleep(2000);
	//limpiamos consola
	system("cls");
	
	printf("---------------------------------------------------------\nTotal vendidio por tipo de producto:\nALIMENTO BALANCEADO: \n  Total vendido: %.2f $\n  Tickets emitidos: %d \nTEXTILES:\n  Total vendido: %.2f $\n  Tickets emitidos: %d \nARTICULOS VARIOS: \n  Total vendido: %.2f $ \n  Tickets emitidos: %d\nMonto total en conceprto de descuentos: %.2f $\nMonto total en concepto de impuestos: %.2f $\nProducto mas caro:\n  Producto: %s \n  Precio: %.2f $\n---------------------------------------------------------\n", vendidoAlimentos, ticketsAlimentos, vendidoTextiles, ticketsTextiles, vendidoVarios, ticketsVarios, totalDescuentos, totalImpuestos, productoMasCaro, precioProductCaro );
	
}

