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
    - [Simulação funcional no Wokwi](https://wokwi.com/projects/414393427034769409)
    - [Simulação com MQTT](https://wokwi.com/projects/414636232313826305) (não funcional devido a instabilidades)
  
- Vídeo explicativo: [Vídeo explicativo](https://youtu.be/r-_TcEO-0Kc)

-----

## Configuração do Simulador Wokwi
1. Acessar o Projeto:

- Clique no [link funcional do Wokwi.](https://wokwi.com/projects/414393427034769409)
- Revise o circuito que contém:
    - Sensor DHT22 (umidade e temperatura).
    - Sensor de luminosidade.
    - Servo Motor representando a válvula de irrigação.
    - LEDs representando iluminação controlada.

2. Testar o Circuito:

- No monitor serial, acompanhe os valores de:
  - Umidade do solo.
  - Estado da válvula de irrigação (aberta/fechada).
  - Estado das luzes (acesas/apagadas).

----

## Simulação no Node-RED

1. Importar Flows
- Baixe os arquivos de flows disponíveis no [GitHub](https://github.com/AngPF/GS-SunWise-IOT.git).
- Importe os flows no Node-RED:
  - Vá em Menu > Import > Cole o JSON do flow.
    
2. Configurar e Testar
- Flow 1: Simulação com valores de entrada via slider.
    - Ajuste a umidade no slider para testar os estados de irrigação e iluminação.
    - Visualize o status em um dashboard com:
        - Gauge de umidade.
        - Histórico gráfico.
  
- Flow 2: Simulação com dados enviados via MQTT.
  - Configure seu broker MQTT e insira os detalhes no nó MQTT.
  - Teste os valores transmitidos para exibição no dashboard.

----

## Configuração MQTT

Preencha as informações de acordo com a imagem abaixo para configurar corretamente o ambiente MQTT:

![image](https://github.com/user-attachments/assets/45702ec1-a576-42b1-8d7e-4f38f0d45fda)

Detalhes do Broker
- **Host:** mqtt-dashboard.com
- **Porta:** 8884

#### Tópico Utilizados
| **Tópico**            | **Descrição**                            | **Exemplo de Payload**                                                                |
|-----------------------|------------------------------------------|--------------------------------------------------------------------------------------|
| `testtopic/teste/gabi/oi`     | Envia dados do sensor para o dashboard      | `{ "umidade": 45, "temperatura": 22.5, "luminosidade": 4095 }`                       |

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
