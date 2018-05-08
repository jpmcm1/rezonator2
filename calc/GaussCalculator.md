# Gauss calculator tool formulas

*Gauss calculator tool* computes some free parameters of Gaussian beam, when changing one of its parameter and fixing some others. As it is not possible to make all the parameters to be free, we introduce two fixing mode called *Lock waist* and *Lock front*.

- Lock waist - find such values of free parameters at which the beam waist stays constant when one of parameters changes.
- Lock front - find such values of free parameters at which the wavefront ROC stays constant when one of parameters changes.

Quadratic equations have two solutions and we have to define a way to point out which solution to take. So the tool has an additional parameter - zone - which can be *Near zone* or *Far zone*.

Test values for the tool is calculated via script `BeamCalculator.py`.

## Change waist

### Lock waist

Calculate the beam radius $w$ and the wavefront ROC $R$ at given distance $z$.

$$ z_0 = \frac{\pi w_0^2}{M^2 \lambda}  $$

$$ V_s = \frac{M^2 \lambda}{\pi w_0}  $$

$$ w = w_0 \sqrt{ 1 + \bigg( \frac{z}{z_0} \bigg)^2 } $$ 

$$ R = z \Bigg[ 1 + \bigg( \frac{z_0}{z} \bigg)^2 \Bigg] $$

$$ q^{-1} = \frac 1 R + i \frac{\lambda}{\pi w^2} $$

### Lock front

For specified waist radius $w_0$, find such a distance $z$ and beam quality $M^2$ at which the wavefront ROC keeps its previously calculated value .

How to find: express $z_0$ from $w(z)$ and from $R(z)$, equate both expressions and solve against $z$.

$$ z = R \Bigg[ 1 - \bigg( \frac{w_0}{w} \bigg)^2 \Bigg] $$

$$ z_0 = \sqrt{ \frac{ z^2 w_0^2 }{ w^2 - w_0^2 } } $$

$$ z_0 = \sqrt{ z (R - z) }  $$

$$ M^2 = \frac{ \pi w_0^2 }{ \lambda z_0 }  $$

$$ V_s = \frac{M^2 \lambda}{\pi w_0}  $$

## Change Rayleigh length

### Lock waist
With fixed waist radius $w_0$, find a value of the beam quality parameter $M^2$ which yields the specified $z_0$.

$$ M^2 = \frac{ \pi w_0^2 }{ \lambda z_0 }  $$

$$ V_s = \frac{M^2 \lambda}{\pi w_0}  $$

$$ w = w_0 \sqrt{ 1 + \bigg( \frac{z}{z_0} \bigg)^2 } $$ 

$$ R = z \Bigg[ 1 + \bigg( \frac{z_0}{z} \bigg)^2 \Bigg] $$

$$ q^{-1} = \frac 1 R + i \frac{\lambda}{\pi w^2} $$

### Lock front
For specified $z_0$, find such a distance $z$ and beam quality $M^2$ at which the wavefront ROC keeps its previously calculated value .

$$ z = \frac R 2 \pm \frac{\sqrt{ R^2 - 4 z_0^2 }}2  $$

$+$ sign is for the far zone, $-$ is for the near zone.

$$ w_0 = \sqrt{ \frac{w^2}{1 + \big( z_0/z \big)^2} } $$

$$ M^2 = \frac{ \pi w_0^2 }{ \lambda z_0 }  $$

$$ V_s = \frac{M^2 \lambda}{\pi w_0}  $$