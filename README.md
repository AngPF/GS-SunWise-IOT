# **SunWise**
# GS-DISRUPTIVE ARCHITECTURES: IOT, IOB & GENERATIVE IA

### Membros

- Alberto R. Peruchi – RM99706
- Angelo Augusto Pelluci – RM98310
- Gabrielle da Silva Stanguini – RM98786
- Maria Fernanda Ribeiro Melo – RM98818
- Nicolas Reis do Espírito Santo – RM98819

# Descrição da Solução
A **SunWise** é uma solução para otimização do controle de irrigação e iluminação em estufas agrícolas. 

Ela utiliza sensores para monitoramento de umidade e luminosidade, atuando de forma automatizada para reduzir o consumo de água e energia.

## Passo a Passo para Replicação
### Pré-requisitos
- Conta no Wokwi.
- Ambiente Node-RED instalado localmente ou em nuvem.
- Broker MQTT configurado.
### Links Importantes
- Repositório GitHub: [GS-SunWise-IOT](https://github.com/AngPF/GS-SunWise-IOT.git)
- Projeto no Wokwi:
    - [Simulação com MQTT](https://wokwi.com/projects/414636232313826305) (Poderá haver dificuldades na compilação por instabilidades no servidor do Wokwi)
    - [Simulação funcional no Wokwi - sem MQTT ](https://wokwi.com/projects/414393427034769409)
  
- Vídeo explicativo: [Vídeo explicativo]([https://youtu.be/r-_TcEO-0Kc](https://youtu.be/1FAO4_O5Q_I))

-----

## Configuração do Simulador Wokwi
1. Acessar o Projeto:

- Clique no [link funcional do Wokwi.](https://wokwi.com/projects/414636232313826305)
- Revise o circuito que contém:
    - Sensor DHT22 (umidade e temperatura).
    - Sensor de luminosidade.
    - Servo Motor representando a válvula de irrigação.
    - LEDs representando iluminação controlada.
    - LCD1602 para mostrar o status da válvula de irrigação e taxa de umidade.

2. Testar o Circuito:

- No LCD1602, acompanhe os valores de:
  - Valor da taxa de umidade
  - Status da válvula de irrigação

- No monitor serial, acompanhe os valores de:
  - Valor da umidade do solo.
  - Valor de Luminosidade.
  - Valor da temperatura
 
  Esses valores são enviados via json para o MQTT, assim que a conexão com o topic do MQTT é feita, na compilação do projeto no simulador do WOKWI.

----

## Simulação no Node-RED

1. Importar Flows
- Baixe o arquivo de flows disponíveis no [GitHub](https://github.com/AngPF/GS-SunWise-IOT.git).
- Importe os flows no Node-RED:
  - Vá em Menu > Import > Selecione o arquivo "Flow-final" baixado do repositório.
    
2. Configurar e Testar
- Flow 1: Simulação com valores de entrada via slider.
    - Ajuste a umidade no slider para testar os estados de irrigação e iluminação.
    - Visualize o status em um dashboard com:
        - Gauge de umidade.
        - Histórico gráfico.
  
- Flow 2: Simulação com dados enviados via MQTT.

   - Caso o código com MQTT rode normalmente:
       - Clique no botão "Implementar" no Node-RED e espere o status do nó "mqtt in" aparecer como "conectado"
       - Abra os dashboards do Node-RED
       - Rode o projeto no Wokwi. Espere aparecer o json com as informações no monitor serial, enquanto esse json não aparecer, isso significa que o servidor ainda está se conectando com o MQTT.
       - Volte a página de Dashboards e veja as informações enviadas do circuito aparecerem nos gráficos do Node-Red.

   - Caso o código com MQTT não funcione por instabilidades no servidor do Wokwi:
       - Configure seu broker MQTT e insira os detalhes no nó MQTT como descrito abaixo no tópico "Configurações MQTT".
       - Teste os valores transmitidos para exibição no dashboard.

----

## Configuração MQTT

Preencha as informações de acordo com a imagem abaixo para configurar corretamente o ambiente MQTT:

![broker mqtt](https://github.com/user-attachments/assets/5ee29282-a5ce-48e2-b066-3fa8f2e38814)

Detalhes do Broker
- **Host:** mqtt-dashboard.com
- **Porta:** 8884

#### Tópico Utilizados
| **Tópico**            | **Descrição**                            | **Exemplo de Payload**                                                                |
|-----------------------|------------------------------------------|--------------------------------------------------------------------------------------|
| `fiap/iot/sensors`     | Envia dados do sensor para o dashboard      | `{ "umidade": 45, "temperatura": 22.5, "luminosidade": 4095 }`                       |

----

# Solução de Problemas

1. Erros no Wokwi:

  - O Wokwi apresentou instabilidades durante o desenvolvimento. Caso o projeto com MQTT não funcione, utilize o fluxo de simulação no Node-RED.

2. Node-RED não conecta ao MQTT:

  - Verifique o endereço e as credenciais do broker.
  - Certifique-se de que a porta do broker está aberta e conectada.


---

<p align="center">
  <strong>Obrigado por explorar nossa solução!</strong><br>
  💻 Feito com 💙 pela equipe SunWise 💡
</p>
