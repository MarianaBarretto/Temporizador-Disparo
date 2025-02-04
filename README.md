<h1 align="center">Sistema de Temporização de LEDs - Embarcatech 💻</h1>

<p>Este projeto utiliza o microcontrolador Raspberry Pi Pico para controlar três LEDs (azul, vermelho e verde) em resposta ao pressionamento de um botão. A sequência de LEDs é controlada por temporizadores (alarms) e um sistema de debounce para evitar leituras indesejadas do botão.</p>

<h2>Descrição do Projeto</h2>
<p>O sistema tem como objetivo acionar três LEDs de forma sequencial ao pressionar o botão. O comportamento é o seguinte:</p>
<ul>
    <li>Quando o botão é pressionado, todos os LEDs acendem.</li>
    <li>Após 3 segundos, o LED azul se apaga.</li>
    <li>Após mais 3 segundos, o LED vermelho se apaga.</li>
    <li>Após mais 3 segundos, o LED verde se apaga.</li>
    <li>O botão só pode ser pressionado novamente quando todos os LEDs estiverem apagados.</li>
</ul>
<p>O sistema utiliza a função <code>add_alarm_in_ms()</code> para gerenciar o tempo entre cada evento de desligamento dos LEDs e a função de debounce em software para evitar múltiplas leituras do botão em um curto intervalo.</p>

<h2>Componentes Utilizados</h2>
<ul>
    <li>Microcontrolador: Raspberry Pi Pico</li>
    <li>LEDs: 3 LEDs (azul, vermelho e verde) com resistores de 330 Ω</li>
    <li>Botão (Pushbutton)</li>
</ul>

<h2>Diagrama de Conexões</h2>
<ul>
    <li>LED Verde: GPIO 11</li>
    <li>LED Azul: GPIO 12</li>
    <li>LED Vermelho: GPIO 13</li>
    <li>Botão: GPIO 5 (com pull-up ativado)</li>
</ul>

<h2>Funcionalidades</h2>
<ul>
    <li>Sequência de LEDs: Após pressionar o botão, os LEDs acendem todos juntos, com desligamentos sequenciais a cada 3 segundos (azul, vermelho e verde).</li>
    <li>Debounce: A leitura do botão possui um algoritmo de debounce para evitar múltiplos acionamentos indesejados.</li>
    <li>Bloqueio de Novas Ativações: O botão só pode ser pressionado novamente após a sequência ser concluída (quando o último LED for desligado).</li>
</ul>

<h2>Compilação e Execução</h2>
<p>Instale o SDK do Raspberry Pi Pico seguindo as instruções aqui.</p>
<p>Compile o código com o comando <code>make</code> ou utilize um ambiente de desenvolvimento como o VSCode.</p>
<p>Carregue o código na Raspberry Pi Pico e execute.</p>

<h4>Autor: <strong>Mariana Barretto</strong></h4>